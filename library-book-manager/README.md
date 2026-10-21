# Library Book Management System

Interactive classroom-library request tracker. Add books, list books sorted by author surname and given name, delete a book by title and author, and exit while freeing allocated linked-list nodes.

**Skills:** Structs, linked lists, sorted insertion, duplicate checking, string input, dynamic allocation and cleanup.

```bash
cc -std=c11 -Wall -Wextra -Wpedantic main.c -o library
./library
```

Operation codes:

- `a` — add a book (title, author's first and last name, price, request count)
- `d` — delete a book using its title and author
- `p` — print all books
- `q` — quit

Use nonnegative numeric input and titles up to 100 characters. The program expects interactive input and does not fully handle unexpected EOF or malformed numeric entries.
