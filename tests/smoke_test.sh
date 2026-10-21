#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT
CC="${CC:-cc}"

build() {
  "$CC" -std=c11 -Wall -Wextra -Wpedantic "$ROOT/$1/main.c" -o "$TMP/$1"
}

build word-frequency-analyzer
build rpn-calculator
build library-book-manager
build word-replacement

"$TMP/word-frequency-analyzer" "$ROOT/word-frequency-analyzer/sample.txt" > "$TMP/frequency-out.txt"
printf 'apple 3\nbanana 2\ndog 1\n' > "$TMP/frequency-expected.txt"
diff -u "$TMP/frequency-expected.txt" "$TMP/frequency-out.txt"

echo 'PASS: word frequency analyzer'

printf '8\n3\n+\n2\n*\nexit\n' | "$TMP/rpn-calculator" > "$TMP/rpn-out.txt"
grep -q 'result of 22' "$TMP/rpn-out.txt"
echo 'PASS: RPN calculator'

printf 'a\nSample Book\nJane\nDoe\n12.99\n3\np\nd\nSample Book\nJane\nDoe\nq\n' | "$TMP/library-book-manager" > "$TMP/library-out.txt"
grep -q 'Sample Book' "$TMP/library-out.txt"
grep -q 'book deleted' "$TMP/library-out.txt"
echo 'PASS: library book manager'

"$TMP/word-replacement" 'cat and cat' 'cat' 'dog' > "$TMP/replace-out.txt"
printf 'dog and dog\n' > "$TMP/replace-expected.txt"
diff -u "$TMP/replace-expected.txt" "$TMP/replace-out.txt"
echo 'PASS: word replacement'

echo 'All four smoke tests passed.'
