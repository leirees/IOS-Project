#include "string.h"

char *concat(char *str1, char *str2)
{
    unsigned long length = strlen(str1) + strlen(str2);
    char *pointer = (char *) malloc(length);

    for (int i = 0; i < strlen(str1); i++)
    {
        pointer[i] = str1[i];
    }

    for (int i = 0; i < strlen(str2); i++)
    {
        pointer[i + strlen(str1)] = str2[i];
    }

    return pointer;
}

void print(char *str)
{
    // Resets the color of the element, in order to only print
    // colored the text we want.
    char *r = concat(str, ANSI_COLOR_RESET);
    write(1, r, strlen(r));
}

void println(char *str)
{
    print(concat(str, "\n"));
}
