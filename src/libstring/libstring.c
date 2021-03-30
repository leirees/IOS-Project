/**
 * @file string.c
 * @author David Cuenca Marcos
 * @brief Modified string library implementation.
 * @version 0.1
 * @date 2021-03-26
 * 
 * @copyright Copyright (c) 2021
 */

#include "../headers/libstring.h"

char * concat(char * str1, char * str2)
{
    unsigned int result_length = strlen(str1) + strlen(str2);
    char * result = (char *) malloc(result_length);

    for (unsigned int i = 0; i < strlen(str1); i++) 
    {
        result[i] = str1[i];
    }

    for (unsigned int i = 0; i < strlen(str2); i++) 
    {
        result[i + strlen(str1)] = str2[i];
    }

    return result;
}

void print(char * str) 
{
    char * result = concat(str, ANSI_COLOR_RESET); 
    int buff = write(1, result, strlen(result));
}

void println(char * str)
{
    char * result = concat(concat(str, ANSI_COLOR_RESET), "\n"); 
    int buff = write(1, result, strlen(result));
}

void printerr(char * str)
{
    char * result = concat(ANSI_COLOR_RED, concat(concat(str, ANSI_COLOR_RESET), "\n")); 
    int buff = write(2, result, strlen(result));
    buff = write(1, ANSI_COLOR_RESET, strlen(ANSI_COLOR_RESET));
}