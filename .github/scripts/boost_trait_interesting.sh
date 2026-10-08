#!/usr/bin/env bash
set -u

src="${1:?candidate source required}"
log="$(mktemp)"
obj="$(mktemp --suffix=.o)"
trap 'rm -f "$log" "$obj"' EXIT

LC_ALL=C g++ -x c++ -std=c++17 -c "$src" -o "$obj" >"$log" 2>&1
status=$?
[ "$status" -ne 0 ] || exit 1

error_count="$(grep -c 'error:' "$log" || true)"
[ "$error_count" -eq 4 ] || exit 1

first_error="$(grep -m1 'error:' "$log" || true)"
printf '%s\n' "$first_error" | grep -Eq 'is_(un)?signed_values<.*unnamed enum' || exit 1

grep -Eq 'is_unsigned_values<.*unnamed enum.*minus_one' "$log" || exit 1
grep -Eq 'is_unsigned_values<.*unnamed enum.*zero' "$log" || exit 1
grep -Eq 'is_signed_values<.*unnamed enum.*minus_one' "$log" || exit 1
grep -Eq 'is_signed_values<.*unnamed enum.*zero' "$log" || exit 1

exit 0
