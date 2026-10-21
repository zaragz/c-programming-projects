/*
Name: Zara Gonzalez
Program: project5.c

Description:
This program replaces every occurence of a word in a sentence with 
another word of the same length, using pointer-based string processing.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_STRING_LEN     50

void my_strcpy(char* destination, char* source){
    char* d = destination;
    char* s = source;
    int count = 0;

    //If either pointer is NULL, do nothing
    if (destination == NULL || source == NULL) {
        return;
    }

    // Copy character by character until '\0' is found
    while (count <= MAX_STRING_LEN) {
       *d = *s;

       // Stop once the end of the source string is copied
       if (*s == '\0') {
            return;
       }

       d++;
       s++;
       count++;
    }

    // If '\0' is never found within the allowed length, exit
    printf("Unable to find end of string or string too long\n");
    exit(EXIT_FAILURE);
}



size_t my_strlen(const char* s) {
    const char* start;
    const char* p;

    // Return 0 if pointer is NULL
    if (s == NULL) {
        return 0;
    }

    start = s;
    p = s;

    // Move through the string until '\0' is found
    while ((p - start) <= MAX_STRING_LEN) {
        if (*p == '\0') {
            return (size_t)(p - start);
        }
        p++;
    }

    // If '\0' was not found in time, exit
    fputs("Unable to find end of string or string too long\n", stdout);
    exit(EXIT_FAILURE);
}



bool starts_with_word(char* sentence, char* word) {
    char* ps = sentence;
    char* pw = word;
    size_t len_sentence;
    size_t len_word;

    // Return false if either pointer is NULL
    if (sentence == NULL || word == NULL) {
        return false;
    }

    len_sentence = my_strlen(sentence);
    len_word = my_strlen(word);

    // If sentence is shorter than word, it cannot start with it
    if (len_sentence < len_word) {
        return false;
    }

    // Compare each character one by one using pointers
    while (*pw != '\0') {
        if (*ps != *pw) {
            return false;
        }
        ps++;
        pw++;
    }

    return true; 
}


bool overwrite_with_word(char* start, char* replacement) {
    char* ps = start;
    char* pr = replacement;
    size_t len_start;
    size_t len_replacement;

    // Return false if either pointer is NULL
    if (start == NULL || replacement == NULL) {
        return false;
    }

    len_start = my_strlen(start);
    len_replacement = my_strlen(replacement);

    // If replecement is longer, it cannot fit
    if (len_start < len_replacement) {
        return false;
    }

    // Overwrite character by character
    while (*pr != '\0') {
        *ps = *pr;
        ps++;
        pr++;
    }
 
    return true;
}



void overwrite_all_words(char* sentence, char* word, char* replacement) {
    char* p;
    char* after_word;
    size_t len_sentence;
    size_t len_word;
    size_t len_replacement;

    // Return immediately if any argument is NULL
    if (sentence == NULL || word == NULL || replacement == NULL) {
        return;
    }

    len_sentence = my_strlen(sentence);
    len_word = my_strlen(word);
    len_replacement = my_strlen(replacement);

    // Return if the word lengths are different
    if (len_word != len_replacement) {
        return;
    }

    // Return if one of the words is longer than the sentence
    if (len_word > len_sentence || len_replacement > len_sentence) {
        return;
    }

    p = sentence;

    // Walk through the sentence one character at a time
    while (*p != '\0') {

        // Check whether p is at the start of a word
        if (p == sentence || *(p - 1) == ' ') {

            // Check whether the word starts here
            if (starts_with_word(p, word)) {
                after_word = p + len_word;

                // Make sure it is a whole word;
                // either followed by space or end of string
                if (*after_word == '\0' || *after_word == ' ') {
                    overwrite_with_word(p, replacement);
                }
            }
        }
 
        p++;
    }
}



/* This function iterates over a string until it reaches the end
    or finds a newline character. If it finds a newline, it replaces
    it with a null terminator and return immediately.
*/
void remove_end_newline(char* s){
    char* p = s;
    while (*p != '\0') {
        if (*p == '\n') {
            *p = '\0';
            break;
        }
        ++p;
    }
}



/*  This main function provides 2 modes of operation: interactive and command-line.
    In interactive mode, the user is prompted to enter a sentence, a word to replace, 
    and a replacement word. 
    In command-line mode, the user provides these three pieces of information as 
    command-line arguments when running the program. That's the mode required by 
    the instuctions, but the interactive mode is provided for your convenience while 
    testing.
    The program then validates the input according to the specifications and performs 
    the word replacement in the sentence, finally printing the modified sentence to 
    standard output.
*/
int main(int argc, char** argv) {

    char sentence[MAX_STRING_LEN * 2 + 1];      // the sentence to be worked on
    char word[MAX_STRING_LEN * 2 + 1];          // the word to be replaced
    char replacement[MAX_STRING_LEN * 2 + 1];   // the replacement word

    bool interactive = false; // whether to run in interactive mode or command-line mode

    if (argc == 1) {
        // if we have no command-line arguments, run in interactive mode
        interactive = true;
    } else if (argc != 4) {
        // if we don't have exactly 3 command-line arguments, print usage 
        // message and exit with failure
        fputs("Usage: ./a.out \"<sentence>\" \"<word>\" \"<replacement>\"\n", stdout);
        fputs("   or: ./a.out\n", stdout);
        exit(EXIT_FAILURE);
    }

    if(interactive){
        printf("Original sentence (max length %d): ", MAX_STRING_LEN);
        
        // The fgets function is another way to read an entire line
        fgets(sentence, (int)sizeof(sentence), stdin);
        // fgets reads everything on the line, including the newline 
        // character at the end. We don't want that, so we call this 
        // helper function to remove it.
        remove_end_newline(sentence);         

        fputs("\nWord to replace: ", stdout);
        fgets(word, (int)sizeof(word), stdin);
        remove_end_newline(word); 

        fputs("\nReplacement: ", stdout);
        fgets(replacement, (int)sizeof(replacement), stdin);
        remove_end_newline(replacement); 
    } else {
        // In non-interactive mode, we use the command line arguments
        my_strcpy(sentence, argv[1]);
        my_strcpy(word, argv[2]);
        my_strcpy(replacement, argv[3]);
    }

    /* Validate according to spec */
    size_t len_sentence   = my_strlen(sentence);
    size_t len_word       = my_strlen(word);
    size_t len_replacement = my_strlen(replacement);
    
    if (len_sentence == 0 || len_word == 0 || len_replacement == 0) {
        fputs("Unable to process your input\n", stdout);
        exit(EXIT_FAILURE);
    }

    if (len_word != len_replacement) {
        fputs("Unable to process your input\n", stdout);
        exit(EXIT_FAILURE);
    }

    if (len_sentence < len_word || len_sentence < len_replacement) {
        fputs("Unable to process your input\n", stdout);
        exit(EXIT_FAILURE);
    }

    // we call our primary function:
    overwrite_all_words(sentence, word, replacement);
    
    // Display a message before the resulting string (only in interactive mode):
    if(interactive) fputs("\nModified string: ", stdout);

    // Displays the modified sentence: 
    fputs(sentence, stdout);
    fputc('\n', stdout);

    return EXIT_SUCCESS;
}

