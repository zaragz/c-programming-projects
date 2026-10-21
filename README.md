# C Programming Projects

**Language:** C11  
**Focus:** Data structures, file processing, text analysis, pointers, and dynamic memory management

A selection of four C programming projects developed through university coursework. I chose projects that demonstrate reusable programming foundations relevant to software and data-oriented work, rather than uploading every introductory exercise.

## Projects

| Project | What it does | Concepts |
| --- | --- | --- |
| [Word Frequency Analyzer](word-frequency-analyzer/) | Reads text from a file, normalizes alphabetic words, counts occurrences, and sorts by frequency | File I/O, structs, text processing, sorting |
| [RPN Calculator](rpn-calculator/) | Evaluates postfix arithmetic interactively using a linked list | Linked lists, stack-like operations, pointers, dynamic allocation |
| [Library Book Manager](library-book-manager/) | Adds, lists, and removes books in author-sorted order | Linked lists, structs, ordered insertion, memory cleanup |
| [Word Replacement](word-replacement/) | Replaces whole words with equal-length alternatives | Pointer arithmetic, string handling, input validation |

Each folder contains its own source code and usage notes. All programs use standard C libraries and can be compiled with a C11 compiler such as GCC or Clang.

## Build and run

From the repository root, on macOS or Linux:

```bash
# Word frequency analysis
cc -std=c11 -Wall -Wextra -Wpedantic word-frequency-analyzer/main.c -o /tmp/word-frequency
/tmp/word-frequency word-frequency-analyzer/sample.txt

# Reverse Polish Notation calculator (interactive)
cc -std=c11 -Wall -Wextra -Wpedantic rpn-calculator/main.c -o /tmp/rpn-calculator
/tmp/rpn-calculator

# Library book manager (interactive)
cc -std=c11 -Wall -Wextra -Wpedantic library-book-manager/main.c -o /tmp/library-manager
/tmp/library-manager

# Pointer-based word replacement
cc -std=c11 -Wall -Wextra -Wpedantic word-replacement/main.c -o /tmp/word-replace
/tmp/word-replace "cat and cat" "cat" "dog"
```

For Windows, use a C11-compatible compiler and change the executable paths appropriately.

## Testing

Run the included smoke tests from the repository root:

```bash
bash tests/smoke_test.sh
```

The script builds each selected program with `-Wall -Wextra -Wpedantic` and runs basic usage checks. These are introductory coursework projects, not production-hardened utilities; they have documented input limitations.

## Notes on source code

These are curated versions of my coursework submissions; some coursework exercises contained instructor-provided starter code or scaffolding. I preserved the original program structure and made two small safety/consistency changes while packaging (plus minor comment and typo cleanup):

- **Word Frequency Analyzer:** expanded its normalized-word buffer to match the maximum token size read, avoiding a buffer overrun for longer tokens.
- **Library Book Manager:** made the deletion title buffer match the program's declared maximum book-title length.

Further robustness work would include stronger handling of extremely long input, unexpected end-of-file, and numeric overflow. These programs are intended to demonstrate foundational C programming, not to process untrusted production data.

## Author

Zara Gonzalez  
University of South Florida — Information Science (Data Science & Analytics)  
[GitHub profile](https://github.com/zaragz)
