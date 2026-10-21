/*
Zara Gonzalez
Project 2 - Word Frequency Analyzer

Reads words from a text file, normalizes each word,
counts repeated words, and prints the sorted results.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define WORD_LENGTH 1024
#define TOKEN_LENGTH 1024

/* Stores one unique word and its frequency */
struct Word
{
    char word[WORD_LENGTH];
    int count;
};

int main(int argc, char *argv[])
{
    FILE *inputFile;
    struct Word words[MAX_WORDS];
    char token[TOKEN_LENGTH];
    char normalized[WORD_LENGTH];
    int wordCount = 0;
    int i, j;

    /* The program must receive exactly one file path */
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    /* Open the input file for reading */
    inputFile = fopen(argv[1], "r");

    if (inputFile == NULL)
    {
        fprintf(stderr, "Error: Could not open file.\n");
        return 1;
    }

    /* Read one whitespace-separated token at a time */
    while (fscanf(inputFile, "%1023s", token) == 1)
    {
        int normalizedLength = 0;
        int found = -1;

        /*
        * Keep only letters and convert them to lowercase. */
        for (i = 0; token[i] != '\0'; i++)
        {
            if (isalpha((unsigned char)token[i]))
            {
                normalized[normalizedLength] =
                    (char)tolower((unsigned char)token[i]);

                normalizedLength++;
            }
        }

        /* Add the null character to finish the string */
        normalized[normalizedLength] = '\0';

        /* Skip tokens that contain no letters */
        if (normalizedLength == 0)
        {
            continue;
        }

        /* Search for the normalized word in the array */
        for (i = 0; i < wordCount; i++)
        {
            if (strcmp(words[i].word, normalized) == 0)
            {
                found = i;
                break;
            }
        }

        if (found != -1)
        {
            /* The word already exists, so increase its count */
            words[found].count++;
        }
        else if (wordCount < MAX_WORDS)
        {
            /* Add a new unique word */
            strcpy(words[wordCount].word, normalized);
            words[wordCount].count = 1;
            wordCount++;
        }
    }

    fclose(inputFile);

    /*
    * Bubble sort: Higher counts come first, equal counts are sorted alphabetically.
    */
    for (i = 0; i < wordCount - 1; i++)
    {
        for (j = 0; j < wordCount - 1 - i; j++)
        {
            int shouldSwap = 0;

            if (words[j].count < words[j + 1].count)
            {
                shouldSwap = 1;
            }
            else if (words[j].count == words[j + 1].count &&
                     strcmp(words[j].word, words[j + 1].word) > 0)
            {
                shouldSwap = 1;
            }

            if (shouldSwap)
            {
                struct Word temp;

                temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }

    /* Prints one word and its count per line */
    for (i = 0; i < wordCount; i++)
    {
        printf("%s %d\n", words[i].word, words[i].count);
    }

    return 0;
}