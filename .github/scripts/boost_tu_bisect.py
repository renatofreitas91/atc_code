#!/usr/bin/env python3
import json
import pathlib
import re
import shlex
import subprocess
import sys


ROOT = pathlib.Path(__file__).resolve().parents[2]
SOURCE = ROOT / "Advanced Trigonometry Calculator" / "data_processing_core.cpp"
BUILD = ROOT / "build-diagnostic"
LOG_DIR = BUILD / "boost-tu-logs"

EARLY = {
    "getCharArray", "solve", "toSolve", "variableValidator", "convertToNumber"
}
GROUP_A = {
    "higherPrecisionController", "verboseResolutionController",
    "numSystemsController", "manageExpression"
}
GROUP_B = {"processVariable", "complexNumber", "prefixDeterminator"}
GROUP_C = {
    "convert2Exponential", "prefToNumber", "numericalSystems", "calcNow"
}


def masked_cpp(source):
    result = list(source)
    state = "code"
    quote = ""
    index = 0
    while index < len(source):
        char = source[index]
        next_char = source[index + 1] if index + 1 < len(source) else ""
        if state == "code":
            if char == "/" and next_char == "/":
                result[index] = result[index + 1] = " "
                state = "line_comment"
                index += 2
                continue
            if char == "/" and next_char == "*":
                result[index] = result[index + 1] = " "
                state = "block_comment"
                index += 2
                continue
            if char in ('"', "'"):
                quote = char
                result[index] = " "
                state = "string"
        elif state == "line_comment":
            if char == "\n":
                state = "code"
            else:
                result[index] = " "
        elif state == "block_comment":
            if char == "*" and next_char == "/":
                result[index] = result[index + 1] = " "
                state = "code"
                index += 2
                continue
            if char != "\n":
                result[index] = " "
        elif state == "string":
            if char == "\\":
                result[index] = " "
                if index + 1 < len(source):
                    result[index + 1] = " "
                index += 2
                continue
            if char == quote:
                state = "code"
            result[index] = " " if char != "\n" else "\n"
        index += 1
    return "".join(result)


def inventory_functions(source):
    masked = masked_cpp(source)
    functions = []
    boundary = 0
    index = 0
    while index < len(masked):
        char = masked[index]
        if char == ";":
            boundary = index + 1
        elif char == "{":
            prefix = masked[boundary:index]
            if ")" not in prefix:
                depth = 1
                end = index + 1
                while end < len(masked) and depth:
                    depth += (masked[end] == "{") - (masked[end] == "}")
                    end += 1
                boundary = end
                index = end
                continue
            depth = 1
            end = index + 1
            while end < len(masked) and depth:
                depth += (masked[end] == "{") - (masked[end] == "}")
                end += 1
            if depth:
                raise RuntimeError("unbalanced function body")
            signature = source[boundary:index].strip()
            calls = re.findall(r"([A-Za-z_]\w*)\s*\(", masked[boundary:index])
            name = calls[-1] if calls else "<unknown>"
            is_template = bool(re.search(r"template\s*<", signature))
            specialization = bool(re.search(r"template\s*<>", signature))
            functions.append({
                "name": name,
                "signature": " ".join(signature.split()),
                "body_start": index,
                "body_end": end,
                "line": source.count("\n", 0, boundary) + 1,
                "category": ("explicit_specialization" if specialization else
                             "template" if is_template else "non_template"),
                "mp_path": bool(is_template and ("T" in signature or
                                name in (EARLY | GROUP_A | GROUP_B | GROUP_C))),
            })
            boundary = end
            index = end
            continue
        index += 1
    return functions


def stub_functions(source, functions):
    for function in sorted(functions, key=lambda item: item["body_start"], reverse=True):
        source = (source[:function["body_start"]] + "{ throw 0; }" +
                  source[function["body_end"]:])
    return source


def explicit_name(line):
    if not re.match(r"^\s*template\s+.*<mp_float>.*;\s*$", line):
        return None
    match = re.search(r"([A-Za-z_]\w*)<mp_float>", line)
    return match.group(1) if match else None


def without(source, names):
    result = []
    removed = []
    for line in source.splitlines(keepends=True):
        name = explicit_name(line)
        if name in names:
            result.append("// ATC DIAGNOSTIC removed: " + line)
            removed.append(name)
        else:
            result.append(line)
    return "".join(result), removed


def replace_implicit(source, initial=False, exponential=False, calc=False):
    if initial:
        old = ("if (higherPrecision == 1) initialProcessor<mp_float>(values, "
               "(mp_float)0); else initialProcessor<double>(values, 0.0);")
        if source.count(old) != 2:
            raise RuntimeError("expected two implicit initialProcessor sites")
        source = source.replace(old, "initialProcessor<double>(values, 0.0);")
    if exponential:
        old = "return convert2Exponential<mp_float>(boost::get<mp_float>(value));"
        if source.count(old) != 1:
            raise RuntimeError("expected one implicit convert2Exponential site")
        source = source.replace(
            old,
            "return convert2Exponential<double>(precisionValueTo<double>(value));",
        )
    if calc:
        old = ("return calcNow<mp_float>(toCalc, precisionValueTo<mp_float>(result1), "
               "precisionValueTo<mp_float>(result2));")
        if source.count(old) != 1:
            raise RuntimeError("expected one implicit calcNow site")
        source = source.replace(
            old,
            "return calcNow<double>(toCalc, precisionValueTo<double>(result1), "
            "precisionValueTo<double>(result2));",
        )
    return source


def compile_entry():
    entries = json.loads((BUILD / "compile_commands.json").read_text())
    for entry in entries:
        if pathlib.Path(entry["file"]).name == SOURCE.name:
            return entry
    raise RuntimeError("data_processing_core.cpp missing from compile_commands.json")


def command_for(entry, diagnostic_source, output):
    args = entry.get("arguments") or shlex.split(entry["command"])
    args = list(args)
    source_candidates = {str(SOURCE), entry["file"]}
    for index, arg in enumerate(args):
        if arg in source_candidates or pathlib.Path(arg).name == SOURCE.name:
            args[index] = str(diagnostic_source)
        elif index and args[index - 1] == "-o":
            args[index] = str(output)
    insert_at = args.index("-c") if "-c" in args else 1
    args[insert_at:insert_at] = [
        "-ftemplate-backtrace-limit=0",
        "-fdiagnostics-show-template-tree",
        "-fno-diagnostics-show-caret",
    ]
    return args


def main():
    LOG_DIR.mkdir(parents=True, exist_ok=True)
    original = SOURCE.read_text(encoding="cp1252")
    inventory = inventory_functions(original)
    templates = [item for item in inventory if item["category"] != "non_template"]
    inventory_lines = ["category\tline\tname\tmp_path\tsignature"]
    for item in inventory:
        inventory_lines.append(
            f'{item["category"]}\t{item["line"]}\t{item["name"]}\t'
            f'{int(item["mp_path"])}\t{item["signature"]}'
        )
    (LOG_DIR / "function-inventory.tsv").write_text(
        "\n".join(inventory_lines) + "\n", encoding="utf-8"
    )
    quarters = []
    for quarter in range(4):
        start = len(templates) * quarter // 4
        end = len(templates) * (quarter + 1) // 4
        quarters.append(templates[start:end])
    all_names = {name for line in original.splitlines() if (name := explicit_name(line))}
    without_initial = replace_implicit(original, initial=True)
    without_exponential = replace_implicit(original, exponential=True)
    without_calc = replace_implicit(original, calc=True)
    without_implicit = replace_implicit(
        original, initial=True, exponential=True, calc=True
    )
    without_all, _ = without(without_implicit, all_names)
    character_match = re.search(
        r"template<typename T>\s+char character_to_prefDet\(T n\) \{.*?\n\}",
        original,
        flags=re.DOTALL,
    )
    if not character_match:
        raise RuntimeError("character_to_prefDet definition not found")
    character_definition = character_match.group(0)
    character_stub = (
        "template<typename T>\nchar character_to_prefDet(T) {\n"
        "\treturn 'U';\n}"
    )
    without_character = original.replace(character_definition, character_stub)
    typed_character = re.sub(
        r"n\s+(<|>=)\s+(1E-?\d+)",
        r"n \1 (T)\2",
        character_definition,
    )
    if typed_character == character_definition:
        raise RuntimeError("character_to_prefDet thresholds were not typed")
    typed_character_full = original.replace(character_definition, typed_character)
    typed_manage = typed_character_full
    manage_func_compare = 'functionProcessor<T>(func, 0, 0, 0, "") == 0.5'
    if typed_manage.count(manage_func_compare) != 4:
        raise RuntimeError("expected four manageExpression function comparisons")
    typed_manage = typed_manage.replace(
        manage_func_compare,
        'functionProcessor<T>(func, 0, 0, 0, "") == (T)0.5',
    )
    if typed_manage.count("if (check != 0.5)") != 1:
        raise RuntimeError("expected one manageExpression check comparison")
    typed_all_mixed = typed_manage.replace(
        "if (check != 0.5)", "if (check != (T)0.5)"
    )
    for name in ("arith", "func", "prefix"):
        for operator in ("==", "!="):
            old = f"{name} {operator} 0"
            new = f"{name} {operator} (T)0"
            if old not in typed_all_mixed:
                raise RuntimeError(f"missing variableValidator comparison: {old}")
            typed_all_mixed = typed_all_mixed.replace(old, new)
    dirent_compare = "dir->d_type == DT_REG"
    typed_dirent_compare = (
        "static_cast<int>(dir->d_type) == static_cast<int>(DT_REG)"
    )
    if original.count(dirent_compare) != 2:
        raise RuntimeError("expected two dirent d_type comparisons")
    typed_dirent_full = original.replace(dirent_compare, typed_dirent_compare)
    isolated_literal = (
        '#include "stdafx.h"\n'
        "template<typename T> char diagnostic_character(T n) {\n"
        "    return n < 1E-21 ? 'A' : 'U';\n}\n"
        "template char diagnostic_character<mp_float>(mp_float);\n"
    )
    isolated_typed = isolated_literal.replace("n < 1E-21", "n < (T)1E-21")
    variants = [
        ("boost_headers_only", set(),
         "#include <boost/math/special_functions/erf.hpp>\n"
         "#include <boost/multiprecision/cpp_dec_float.hpp>\n"),
        ("precision_types_only", set(), '#include "precision_types.h"\n'),
        ("stdafx_only", set(), '#include "stdafx.h"\n'),
        ("baseline", set(), None),
        ("without_complex_mp", {"complexNumber"}, None),
        ("without_early", EARLY, None),
        ("without_group_a", GROUP_A, None),
        ("without_group_b", GROUP_B, None),
        ("without_group_c", GROUP_C, None),
        ("without_all_explicit_mp", all_names, None),
        ("without_implicit_initial_processor", set(), without_initial),
        ("without_implicit_convert2_exponential", set(), without_exponential),
        ("without_implicit_calcnow", set(), without_calc),
        ("without_all_implicit_mp", set(), without_implicit),
        ("without_all_explicit_and_implicit_mp", set(), without_all),
        ("without_character_to_prefdet", set(), without_character),
        ("isolated_character_literal", set(), isolated_literal),
        ("isolated_character_typed", set(), isolated_typed),
        ("typed_character_thresholds_full_tu", set(), typed_character_full),
        ("typed_all_mixed_comparisons_full_tu", set(), typed_all_mixed),
    ]
    for index, quarter in enumerate(quarters, 1):
        variants.append((f"stub_template_q{index}", set(),
                         stub_functions(original, quarter)))
    for index, quarter in enumerate(quarters, 1):
        keep_ids = {item["body_start"] for item in quarter}
        to_stub = [item for item in templates if item["body_start"] not in keep_ids]
        variants.append((f"only_template_q{index}", set(),
                         stub_functions(original, to_stub)))
    non_templates = [item for item in inventory if item["category"] == "non_template"]
    variants.append(("all_templates_stubbed", set(),
                     stub_functions(original, templates)))
    variants.append(("all_non_templates_stubbed", set(),
                     stub_functions(original, non_templates)))
    non_template_quarters = []
    for quarter in range(4):
        start = len(non_templates) * quarter // 4
        end = len(non_templates) * (quarter + 1) // 4
        non_template_quarters.append(non_templates[start:end])
    for index, quarter in enumerate(quarters, 1):
        keep_ids = {item["body_start"] for item in quarter}
        to_stub = (non_templates +
                   [item for item in templates if item["body_start"] not in keep_ids])
        variants.append((f"isolated_template_q{index}", set(),
                         stub_functions(original, to_stub)))
    for index, quarter in enumerate(non_template_quarters, 1):
        keep_ids = {item["body_start"] for item in quarter}
        to_stub = (templates +
                   [item for item in non_templates if item["body_start"] not in keep_ids])
        variants.append((f"isolated_non_template_q{index}", set(),
                         stub_functions(original, to_stub)))
    causal_candidates = quarters[2] + non_template_quarters[3]
    for function in causal_candidates:
        to_stub = [item for item in inventory
                   if item["body_start"] != function["body_start"]]
        safe_name = re.sub(r"\W+", "_", function["name"]).strip("_") or "unknown"
        variants.append((
            f"isolated_function_{function['line']}_{safe_name}",
            set(),
            stub_functions(original, to_stub),
        ))
    dirent_culprits = ((3955, "toSolve"), (6695, "isContainedInUserFunction"))
    for culprit_line, culprit_name in dirent_culprits:
        matches = [item for item in inventory
                   if item["line"] == culprit_line and item["name"] == culprit_name]
        if len(matches) != 1:
            raise RuntimeError(
                f"dirent culprit inventory mismatch: {culprit_line} {culprit_name}"
            )
        culprit = matches[0]
        reduced = stub_functions(
            original,
            [item for item in inventory if item["body_start"] != culprit["body_start"]],
        )
        if reduced.count(dirent_compare) != 1:
            raise RuntimeError(f"expected one isolated dirent comparison: {culprit_name}")
        variants.append((
            f"isolated_dirent_original_{culprit_name}", set(), reduced,
        ))
        variants.append((
            f"isolated_dirent_typed_{culprit_name}", set(),
            reduced.replace(dirent_compare, typed_dirent_compare),
        ))
    variants.append(("typed_dirent_full_tu", set(), typed_dirent_full))
    entry = compile_entry()
    any_unexpected = False

    print("Real compile command:")
    print(entry.get("command") or shlex.join(entry["arguments"]))
    print("Explicit mp_float names:", ", ".join(sorted(all_names)))

    dirent_probe_source = BUILD / "dirent-type-probe.cpp"
    dirent_probe_binary = BUILD / "dirent-type-probe"
    dirent_probe_source.write_text(
        "#include <dirent.h>\n"
        "#include <type_traits>\n"
        "static_assert(std::is_same<decltype(dirent{}.d_type), unsigned char>::value, "
        "\"unexpected POSIX dirent::d_type\");\n"
        "static_assert(std::is_enum<decltype(DT_REG)>::value, "
        "\"DT_REG must expose the anonymous enum trigger\");\n"
        "int main() {\n"
        "  const unsigned char values[] = {DT_REG, DT_DIR, DT_UNKNOWN, DT_FIFO};\n"
        "  for (unsigned char value : values) {\n"
        "    if ((value == DT_REG) != "
        "(static_cast<int>(value) == static_cast<int>(DT_REG))) return 1;\n"
        "  }\n"
        "  return 0;\n"
        "}\n",
        encoding="utf-8",
    )
    compiler = (entry.get("arguments") or shlex.split(entry["command"]))[0]
    dirent_probe_compile = subprocess.run(
        [compiler, "-std=c++17", str(dirent_probe_source),
         "-o", str(dirent_probe_binary)],
        stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
        text=True, errors="replace",
    )
    dirent_probe_run = subprocess.run(
        [str(dirent_probe_binary)], stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT, text=True, errors="replace",
    ) if dirent_probe_compile.returncode == 0 else None
    (LOG_DIR / "dirent-type-probe.log").write_text(
        dirent_probe_compile.stdout +
        (dirent_probe_run.stdout if dirent_probe_run else ""), encoding="utf-8"
    )
    print(
        f"DIRENT_TYPE_RESULT compile_exit={dirent_probe_compile.returncode} "
        f"run_exit={dirent_probe_run.returncode if dirent_probe_run else 'NA'} "
        "d_type=unsigned_char DT_REG=enum cast=int"
    )
    if (dirent_probe_compile.returncode != 0
            or not dirent_probe_run or dirent_probe_run.returncode != 0):
        any_unexpected = True

    for label, names, custom_text in variants:
        text, removed = without(original, names)
        if custom_text is not None:
            text = custom_text
        diagnostic_source = SOURCE.with_name("data_processing_core_atc_diagnostic.cpp")
        diagnostic_source.write_text(text, encoding="cp1252")
        output = BUILD / (label + ".o")
        args = command_for(entry, diagnostic_source, output)
        completed = subprocess.run(
            args,
            cwd=entry["directory"],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            errors="replace",
        )
        log = completed.stdout
        (LOG_DIR / (label + ".log")).write_text(log, encoding="utf-8")
        trait_hits = sum(log.count(token) for token in (
            "is_unsigned_values<<unnamed enum>",
            "is_signed_values<<unnamed enum>",
        ))
        errors = len(re.findall(r"(?:fatal )?error:", log))
        error_lines = [line for line in log.splitlines() if "error:" in line]
        unsigned_hits = sum("is_unsigned_values" in line for line in error_lines)
        signed_hits = sum("is_signed_values" in line for line in error_lines)
        other_errors = [line for line in error_lines
                        if "is_unsigned_values" not in line
                        and "is_signed_values" not in line]
        print(
            f"RESULT {label}: exit={completed.returncode} errors={errors} "
            f"trait_hits={trait_hits} removed={','.join(removed) or '-'}"
        )
        if (label.startswith(("stub_template_", "only_template_"))
                or label.startswith(("isolated_template_", "isolated_non_template_"))
                or label.startswith("isolated_function_")
                or label.startswith("isolated_dirent_")
                or label == "typed_dirent_full_tu"
                or label in ("all_templates_stubbed", "all_non_templates_stubbed")):
            print(
                f"CASE_RESULT {label}\texit={completed.returncode}"
                f"\tunsigned={unsigned_hits}\tsigned={signed_hits}"
                f"\ttotal={unsigned_hits + signed_hits}"
                f"\tfirst_other={other_errors[0] if other_errors else '-'}"
            )
        if label == "baseline" and trait_hits == 0:
            any_unexpected = True
        causal_expectation = None
        if label.startswith("isolated_dirent_original_"):
            causal_expectation = (False, 2, 2)
        elif label.startswith("isolated_dirent_typed_"):
            causal_expectation = (True, 0, 0)
        elif label == "typed_dirent_full_tu":
            causal_expectation = (True, 0, 0)
        if causal_expectation is not None:
            expect_success, expect_unsigned, expect_signed = causal_expectation
            actual_success = completed.returncode == 0
            if (actual_success != expect_success
                    or unsigned_hits != expect_unsigned
                    or signed_hits != expect_signed
                    or other_errors):
                any_unexpected = True
                print(
                    f"CAUSAL_EXPECTATION_FAILED {label}: "
                    f"success={actual_success} unsigned={unsigned_hits} "
                    f"signed={signed_hits} first_other="
                    f"{other_errors[0] if other_errors else '-'}"
                )

    # Confirm that each independently causal reduced source survives
    # preprocessing and still reaches all four Boost trait diagnostics.
    for culprit_line, culprit_name in dirent_culprits:
        matches = [item for item in inventory
                   if item["line"] == culprit_line and item["name"] == culprit_name]
        if len(matches) != 1:
            raise RuntimeError(f"culprit inventory mismatch: {culprit_line} {culprit_name}")
        culprit = matches[0]
        reduced = stub_functions(
            original,
            [item for item in inventory if item["body_start"] != culprit["body_start"]],
        )
        diagnostic_source.write_text(reduced, encoding="cp1252")
        ii_path = BUILD / f"trigger-{culprit_name}.ii"
        preprocess_args = command_for(
            entry, diagnostic_source, BUILD / f"trigger-{culprit_name}.unused"
        )
        preprocess_args[preprocess_args.index("-c")] = "-E"
        preprocess_args[preprocess_args.index(str(diagnostic_source))] = str(diagnostic_source)
        preprocess_args[preprocess_args.index("-o") + 1] = str(ii_path)
        preprocessed = subprocess.run(
            preprocess_args, cwd=entry["directory"],
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
            text=True, errors="replace",
        )
        compile_args = list(preprocess_args)
        compile_args[compile_args.index("-E")] = "-c"
        compile_args[compile_args.index(str(diagnostic_source))] = str(ii_path)
        compile_args[compile_args.index("-o") + 1] = str(
            BUILD / f"trigger-{culprit_name}.o"
        )
        compiled = subprocess.run(
            compile_args, cwd=entry["directory"],
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
            text=True, errors="replace",
        ) if preprocessed.returncode == 0 else None
        ii_log = compiled.stdout if compiled else preprocessed.stdout
        (LOG_DIR / f"trigger-{culprit_name}-ii.log").write_text(
            ii_log, encoding="utf-8"
        )
        error_lines = [line for line in ii_log.splitlines() if "error:" in line]
        unsigned = sum("is_unsigned_values" in line for line in error_lines)
        signed = sum("is_signed_values" in line for line in error_lines)
        print(
            f"II_RESULT {culprit_name}: preprocess_exit={preprocessed.returncode} "
            f"compile_exit={compiled.returncode if compiled else 'NA'} "
            f"unsigned={unsigned} signed={signed} total={unsigned + signed}"
        )

    # Diagnostic only: allow GCC to emit the object so the exact undefined
    # trait symbols can be identified. This flag is never used for a product
    # build and the resulting object is not linked.
    diagnostic_source.write_text(typed_all_mixed, encoding="cp1252")
    output = BUILD / "permissive-symbol-probe.o"
    args = command_for(entry, diagnostic_source, output)
    args.insert(args.index("-c"), "-g")
    args.insert(args.index("-c"), "-fpermissive")
    completed = subprocess.run(
        args,
        cwd=entry["directory"],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        errors="replace",
    )
    (LOG_DIR / "permissive-symbol-probe.log").write_text(
        completed.stdout, encoding="utf-8"
    )
    print(f"RESULT typed_permissive_symbol_probe: exit={completed.returncode}")
    if completed.returncode == 0:
        symbols = subprocess.run(
            ["nm", "-C", str(output)],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            errors="replace",
            check=False,
        ).stdout
        (LOG_DIR / "permissive-symbols.txt").write_text(symbols, encoding="utf-8")
        for line in symbols.splitlines():
            if "is_unsigned_values" in line or "is_signed_values" in line:
                print("TRAIT_SYMBOL", line)
            if "is_valid_mixed_compare" in line and "double" in line:
                print("MIXED_COMPARE_SYMBOL", line)
        disassembly = subprocess.run(
            ["objdump", "-drC", str(output)],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            errors="replace",
            check=False,
        ).stdout
        (LOG_DIR / "permissive-disassembly.txt").write_text(
            disassembly, encoding="utf-8"
        )
        current_function = ""
        callers = set()
        for line in disassembly.splitlines():
            if re.match(r"^[0-9a-f]+ <.*>:$", line):
                current_function = line
            if ("is_valid_mixed_compare" in line and "double" in line
                    and "operator<" in line):
                callers.add(current_function)
        for caller in sorted(callers):
            print("MIXED_COMPARE_CALLER", caller)

    diagnostic_source.unlink(missing_ok=True)
    return 2 if any_unexpected else 0


if __name__ == "__main__":
    sys.exit(main())
