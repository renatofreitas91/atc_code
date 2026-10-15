#!/usr/bin/env bash
# Run this from a normal Ubuntu terminal, outside a ptrace-restricted sandbox.
set -u
if [[ $# -lt 1 || $# -gt 2 ]]; then
    echo "Usage: bash $0 /path/to/instrumented/atc [output-directory]" >&2
    exit 2
fi
script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)" || exit 2
exe="$(realpath -- "$1")" || exit 2
if [[ ! -x "$exe" ]]; then
    echo "Executable not found: $exe" >&2
    exit 2
fi
log_dir="${2:-outputs/lsan-remaining-$(date -u +%Y%m%dT%H%M%SZ)}"
if [[ -e "$log_dir" ]]; then
    echo "Output directory already exists; choose a new directory: $log_dir" >&2
    exit 2
fi
mkdir -p -- "$log_dir" || exit 2
export ASAN_OPTIONS=detect_leaks=1:halt_on_error=1
export UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1
export LSAN_OPTIONS=verbosity=1:log_threads=1
python3 - "$exe" "$log_dir" <<'PY'
import hashlib,json,os,subprocess,sys
from pathlib import Path
executable=Path(sys.argv[1]);directory=Path(sys.argv[2])
runtime=subprocess.run(['ldd',str(executable)],capture_output=True,text=True)
if runtime.returncode != 0 or 'libasan.so' not in runtime.stdout:
    raise SystemExit('This driver requires the existing GCC executable dynamically linked to libasan; use build-opt-san/atc.')
(directory/'runtime-libraries.txt').write_text(runtime.stdout+runtime.stderr)
with executable.open('rb') as stream:
    digest=hashlib.file_digest(stream,'sha256').hexdigest() if hasattr(hashlib,'file_digest') else None
# Ubuntu versions with Python <3.11 also support recording the hash.
if digest is None:
    h=hashlib.sha256()
    with executable.open('rb') as stream:
        for chunk in iter(lambda:stream.read(1024*1024),b''):h.update(chunk)
    digest=h.hexdigest()
metadata={'executable':str(executable),'binary_sha256':digest,
          'environment':{name:os.environ[name] for name in ['ASAN_OPTIONS','UBSAN_OPTIONS','LSAN_OPTIONS']}}
(directory/'environment.json').write_text(json.dumps(metadata,indent=2))
PY
if [[ $? -ne 0 ]]; then exit 2; fi
failed=0
for suite in input graph terminal; do
    case "$suite" in
        input) runner=run-atc-linux-input-smoke.py; options=() ;;
        graph) runner=run-atc-linux-graph.py; options=(--timeout 300 --output-dir "$log_dir/graph-details") ;;
        terminal) runner=run-atc-linux-terminal.py; options=(--timeout 60 --output-dir "$log_dir/terminal-details") ;;
    esac
    echo "A executar $suite com LSan; os gráficos podem demorar vários minutos..."
    python3 "$script_dir/$runner" "$exe" "${options[@]}" > "$log_dir/$suite.log" 2>&1
    result=$?
    printf '%s: código de saída %d\n' "$suite" "$result" | tee -a "$log_dir/resumo.txt"
    if [[ $result -ne 0 ]]; then failed=1; fi
 done
printf '\nLogs guardados em: %s\n' "$log_dir"
exit "$failed"
