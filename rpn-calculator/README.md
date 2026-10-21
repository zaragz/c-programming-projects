# Reverse Polish Notation Calculator

Interactive integer calculator: enter operands and operators (`+`, `-`, `*`, `/`) one at a time. The program stores values in a linked list and applies operators to the two most recent operands. Type `exit` to quit.

**Skills:** Linked lists, manual allocation/freeing, stack-style operations, input parsing, arithmetic validation.

```bash
cc -std=c11 -Wall -Wextra -Wpedantic main.c -o rpn
./rpn
```

Example session inputs:

```text
8
3
+
2
*
exit
```

The calculation produces a result of `22`. Division uses integer arithmetic. The code guards against division by zero and insufficient operands but is not hardened against integer overflow.

**Coursework note:** The submission included a provided driver and parsing helpers; my implementation focused on linked-list operations and integrating them into the calculator.
