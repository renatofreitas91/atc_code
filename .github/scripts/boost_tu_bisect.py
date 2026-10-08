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
    variants = [
        ("baseline", set()),
        ("without_complex_mp", {"complexNumber"}),
        ("without_early", EARLY),
        ("without_group_a", GROUP_A),
        ("without_group_b", GROUP_B),
        ("without_group_c", GROUP_C),
        ("without_all_explicit_mp", all_names),
    ]
    entry = compile_entry()
    any_unexpected = False

    print("Real compile command:")
    print(entry.get("command") or shlex.join(entry["arguments"]))
    print("Explicit mp_float names:", ", ".join(sorted(all_names)))

    for label, names in variants:
        text, removed = without(original, names)
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

    diagnostic_source.unlink(missing_ok=True)
    return 2 if any_unexpected else 0


if __name__ == "__main__":
    sys.exit(main())
