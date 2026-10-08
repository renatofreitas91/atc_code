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
    entry = compile_entry()
    any_unexpected = False

    print("Real compile command:")
    print(entry.get("command") or shlex.join(entry["arguments"]))
    print("Explicit mp_float names:", ", ".join(sorted(all_names)))

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
        print(
            f"RESULT {label}: exit={completed.returncode} errors={errors} "
            f"trait_hits={trait_hits} removed={','.join(removed) or '-'}"
        )
        if label == "baseline" and trait_hits == 0:
            any_unexpected = True

    # Diagnostic only: allow GCC to emit the object so the exact undefined
    # trait symbols can be identified. This flag is never used for a product
    # build and the resulting object is not linked.
    diagnostic_source.write_text(original, encoding="cp1252")
    output = BUILD / "permissive-symbol-probe.o"
    args = command_for(entry, diagnostic_source, output)
    args = [arg for arg in args if arg not in ("-O1", "-O2", "-O3", "-Os")]
    args.insert(args.index("-c"), "-O0")
    args.insert(args.index("-c"), "-g")
    args.insert(args.index("-c"), "-fno-inline")
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
    print(f"RESULT permissive_symbol_probe: exit={completed.returncode}")
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
