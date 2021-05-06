/**
 * @file string.c
 * @author David Cuenca Marcos
 * @brief Modified string library implementation.
 * @version 0.1
 * @date 2021-03-26
 * 
 * @copyright Copyright (c) 2021
 */

#include "libstring.h"
#include <stdlib.h>
#include <unistd.h>

char *concat(char *str1, char *str2)
{
    size_t length_str1 = strlen(str1);
    size_t length_str2 = strlen(str2);

    int i;
    char *r_string = (char *)malloc(length_str1 + length_str2);

    for (i = 0; i < length_str1; i++)
    {
        r_string[i] = str1[i];
    }

    for (i = 0; i < length_str2; i++)
    {
        r_string[i + length_str1] = str2[i];
    }

    return r_string;
}

int strcomp(char *str1, char *str2)
{
    return !strcmp(str1, str2);
}

void print(char *str)
{
    char *result;
    ssize_t buff;

    result = concat(str, ANSI_COLOR_RESET);
    buff = write(1, result, strlen(result));
}

void println(char *str)
{
    print(concat(str, "\n"));
}

void printerr(char *str, char *err_title)
{
    char *result = concat(concat(concat(err_title, ": "), str), "\n");
    ssize_t buff = write(2, result, strlen(result));
}

char *bold(char *str)
{
    return concat(concat(BOLD, str), NO_BOLD);
}

char *underlined(char *str)
{
    return concat(concat(UNDERLINE, str), NO_UNDERLINE);
}

char *reversed(char *str)
{
    return concat(concat(REVERSE, str), NO_REVERSE);
}