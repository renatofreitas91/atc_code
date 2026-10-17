#!/usr/bin/env python3
"""Compile the real directory-search function and check its resource lifetime."""
import argparse
import os
from pathlib import Path
import subprocess
import tempfile


PRELUDE = r'''
#include <dirent.h>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <sys/stat.h>
constexpr int DIM = 3100;
char atcPath[DIM];
int strStart = 0, opened = 0, closed = 0;
DIR* live = nullptr;
DIR* trackedOpen(const char* path) {
    assert(live == nullptr);
    live = opendir(path);
    if (live) ++opened;
    return live;
}
int trackedClose(DIR* handle) {
    assert(handle && handle == live);
    ++closed;
    live = nullptr;
    return closedir(handle);
}
char* getDynamicCharArray(const char* initial, const char*) {
    auto value = new char[DIM]();
    std::strcpy(value, initial);
    return value;
}
void _delete(char* value, const char*) { delete[] value; }
void atcJoinPath(char* out, int size, const char* parent, const char* name) {
    std::snprintf(out, size, "%s/%s", parent, name);
}
bool searchExtension(const char* value, const char* suffix) {
    size_t a = std::strlen(value), b = std::strlen(suffix);
    return a >= b && std::strcmp(value + a - b, suffix) == 0;
}
bool isContained(const char* needle, const char* haystack) {
    auto match = std::strstr(haystack, needle);
    if (match) strStart = int(match - haystack);
    return match != nullptr;
}
bool isEqual(const char* a, const char* b) { return std::strcmp(a, b) == 0; }
#define opendir trackedOpen
#define closedir trackedClose
'''

MAIN = r'''
#undef opendir
#undef closedir
int main(int argc, char** argv) {
    assert(argc == 2);
    std::snprintf(atcPath, sizeof(atcPath), "%s", argv[1]);
    char variable[] = "target";
    auto check = [&](bool expected, int expectedOpens) {
        int before = opened;
        assert(isContainedInUserFunction(variable) == expected);
        assert(opened - before == expectedOpens);
        assert(opened == closed && live == nullptr);
    };
    check(false, 0); // Failed opendir must not be closed.
    std::puts("PASS missing directory");
    std::string directory = std::string(atcPath) + "/User functions";
    assert(mkdir(directory.c_str(), 0700) == 0);
    for (int i = 0; i < 100; ++i) check(false, 1);
    std::puts("PASS empty directory: 100 balanced opens/closes");
    { std::ofstream(directory + "/other.txt") << "1"; }
    { std::ofstream(directory + "/target.dat") << "1"; }
    for (int i = 0; i < 100; ++i) check(false, 1);
    std::puts("PASS unmatched files: 100 balanced opens/closes");
    { std::ofstream(directory + "/target.txt") << "1"; }
    for (int i = 0; i < 100; ++i) check(true, 1);
    std::puts("PASS matching file early return: 100 balanced opens/closes");
}
'''


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path)
    parser.add_argument('--compiler', default='g++')
    parser.add_argument('--sanitize', action='store_true')
    parser.add_argument('--leaks', action='store_true')
    args = parser.parse_args()
    source = args.source or Path(__file__).resolve().parents[1]/'Advanced Trigonometry Calculator/data_processing_core.cpp'
    text = source.read_bytes().decode('latin1')
    start = text.index('bool isContainedInUserFunction(char* variable) {')
    end = text.index('static bool appendToDynamicTextBuffer', start)
    with tempfile.TemporaryDirectory(prefix='atc-directory-lifetime-') as directory:
        root = Path(directory)
        cpp, executable = root/'check.cpp', root/'check'
        cpp.write_text(PRELUDE + text[start:end] + MAIN)
        argv = [args.compiler, '-std=c++17', '-O3', '-g', str(cpp), '-o', str(executable)]
        if args.sanitize or args.leaks:
            argv += ['-fsanitize=address,undefined', '-fno-omit-frame-pointer']
        subprocess.run(argv, check=True)
        env = dict(os.environ)
        env['ASAN_OPTIONS'] = 'detect_leaks='+('1' if args.leaks else '0')+':halt_on_error=1:abort_on_error=1'
        env['UBSAN_OPTIONS'] = 'halt_on_error=1:print_stacktrace=1'
        if not args.leaks:
            env.pop('LSAN_OPTIONS', None)
        return subprocess.run([str(executable), str(root)], env=env).returncode


if __name__ == '__main__':
    raise SystemExit(main())
