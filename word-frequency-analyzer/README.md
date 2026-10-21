# Word Frequency Analyzer

Reads whitespace-separated tokens from a text file, removes nonalphabetic characters, converts to lowercase, and counts distinct words. Prints words in descending frequency order, breaking ties alphabetically.

**Skills:** File I/O (`fopen`, `fscanf`, `fclose`), structs, token normalization, search, bubble sort.

```bash
cc -std=c11 -Wall -Wextra -Wpedantic main.c -o frequency
./frequency sample.txt
```

Example output:

```text
apple 3
banana 2
dog 1
```

**Limitations:** Supports up to 1,000 distinct words and reads tokens up to 1,023 characters per scan; longer whitespace-separated tokens may be split. The normalization removes punctuation rather than treating all punctuation as word boundaries.
