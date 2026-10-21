/*
   Zara Gonzalez
   project8.c

   Description:
   This program implements a Reverse Polish Notation (RPN) calculator using a linked list.
   The user enters operands (integers) and operators (+, -, *, /) one at a time.
   Operands are stored in a linked list, and when an operator is entered, the program
   removes the last two operands, applies the operation, and stores the result back
   into the list. The program also handles invalid inputs and ensures there are enough
   operands before performing operations.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// -------------------------------------------------
// Defining the Linked List Structure and data type:
// -------------------------------------------------

typedef struct Node {
    int value;
    struct Node *next;
} Node;



// ---------------------------------------------
// Linked-list operations:
// ---------------------------------------------


// Append a value to the end of the linked list
Node* add_end(Node *head, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node *temp;

    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }

    newNode->value = value;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;

    return head;
}

// Linked-list helper
Node* remove_last(Node *head, int *out) {
    Node *temp;
    Node *prev;

    if (out == NULL) {
        printf("Function remove_last called without proper arguments\n");
        exit(EXIT_FAILURE);
    }

    if (head == NULL) {
        return head;
    }

    if (head->next == NULL) {
        *out = head->value;
        free(head);
        return NULL;
    }

    prev = NULL;
    temp = head;

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    *out = temp->value;
    prev->next = NULL;
    free(temp);

    return head;
}

// Linked-list helper
void print_list(Node *head) {
    Node *temp = head;

    printf("The linked list contains:");
    if (temp != NULL) {
        printf(" ");
    }

    while (temp != NULL) {
        printf("[%d]", temp->value);
        temp = temp->next;
    }

    printf("\n");
}

// Linked-list helper
void clear_list(Node **head) {
    Node *temp;

    if (head == NULL) {
        return;
    }

    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}


// ----------------------------------------------------
// The following functions are already provided to you:
// ----------------------------------------------------

/* Returns 1 if s is a valid integer (no extra characters), puts value in *out */
int parse_int_strict(const char *s, int *out) {
    char *endptr = NULL;
    long val = strtol(s, &endptr, 10);
    if (s[0] == '\0' || *endptr != '\0') return 0;  // must consume entire string
    *out = (int)val;
    return 1;
}

/* Returns 1 if s is exactly one of + - * / */
int is_operator(const char *s) {
    return (strlen(s) == 1 && (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/'));
}



// -------------------------------------
// Main function (also provided to you):
// -------------------------------------


int main(void) {
    Node *list = NULL;
    char token[128];

    printf("Welcome to our RPN calculator!\n");

    for (;;) {
        printf("\nEnter an operand or operator: ");

        /* Read a single word (no spaces) */
        if (scanf("%127s", token) != 1) break;

        /* Empty the rest of the line as required */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { /* discard */ }

        /* Exit command */
        if (strcmp(token, "exit") == 0) {
            printf("\nThank you for using the RPN calculator!\n");
            break;
        }

        /* If token is an integer, append and print list */
        int value;
        if (parse_int_strict(token, &value)) {
            list = add_end(list, value);
            print_list(list);
            continue;
        }

        /* If token is an operator, attempt to apply to last two values */
        if (is_operator(token)) {
            int b, a;
            if (list == NULL){ // empty list, no operands
                printf("--> ERROR: Not Enough Operands entered so far\n");
                continue;
            } else if (list->next == NULL){ // only one operand
                printf("--> ERROR: Not Enough Operands entered so far\n");
                continue;
            }
            // we know there are at least two operands, so we can safely remove them
            list = remove_last(list, &b);
            list = remove_last(list, &a);

            int result = 0;
            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) {
                        /* Not specified as a special error in the prompt; treat as invalid input. */
                        printf("--> ERROR: Invalid Input: \"%s\"\n", token);
                        /* Restore original operands to preserve state */
                        list = add_end(list, a);
                        list = add_end(list, b);
                        continue;
                    }
                    result = a / b;  /* integer division */
                    break;
            }

            /* Print operation in the order shown (last, then second-last) */
            printf("Applying operator %c to operands %d and %d for a result of %d\n",
                   token[0], b, a, result);

            list = add_end(list, result);
            print_list(list);
            continue;
        }

        /* Otherwise: invalid input */
        printf("--> ERROR: Invalid Input: \"%s\"\n", token);
    }

    clear_list(&list);
    return EXIT_SUCCESS;
}
