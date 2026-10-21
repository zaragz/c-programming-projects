# Pointer-Based Word Replacement

Replaces whole words in a sentence with a different word of the same length, using custom pointer-based string functions rather than the usual standard string utilities. Supports command-line and interactive use.

**Skills:** Pointers, null-terminated strings, manual copy/length routines, validation and string traversal.

```bash
cc -std=c11 -Wall -Wextra -Wpedantic main.c -o replace
./replace "cat and cat" "cat" "dog"
```

Output:

```text
dog and dog
```

Run `./replace` with no arguments for interactive mode. Replacements must be the same length as the original word, and word boundaries are defined by spaces or the beginning/end of the sentence. It is designed for short input (up to 50 characters as validated by the custom length function).

**Coursework note:** The original assignment included a driver scaffold; my implementation completed the pointer-based helper functions.
