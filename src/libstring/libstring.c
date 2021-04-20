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

char *concat(char *str1, char *str2)
{
    size_t length_str1  = strlen(str1);
    size_t length_str2  = strlen(str2);
    size_t total_length = length_str1 + length_str2;
    
    char *r_string = (char *) malloc(total_length);

    for (__U16_TYPE i = 0; i < length_str1; i++) 
    {
        r_string[i] = str1[i];
    }

    for (__U16_TYPE i = 0; i < length_str2; i++) 
    {
        r_string[i + length_str1] = str2[i];
    }

    return r_string;
}

void print(char *str) 
{
    char *result = concat(str, ANSI_COLOR_RESET); 
    ssize_t buff = write(1, result, strlen(result));
}

void println(char *str)
{
    char *color = concat(ANSI_COLOR_RESET, "\n");
    char *result = concat(str, color); 
    ssize_t buff = write(1, result, strlen(result));
}

void printerr(char *str)
{
    char *system = THE_SYSTEM;
    char *result = concat(
            concat(concat(system, ": "), str), "\n"
            ); 
            
    ssize_t buff = write(2, result, strlen(result));
    buff = write(1, ANSI_COLOR_RESET, strlen(ANSI_COLOR_RESET));
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

void speak_glinda(char *text, int is_short)
{
    char *glinda;

    if (is_short)
    {
        glinda = SHORT_GLINDA;
    }
    else
    {
        glinda = GLINDA;
    }

    println("");
    println(concat(concat(glinda, ": "), text));
}

void speak_ofelia(char *text, int is_short)
{
    char *ofelia;

    if (is_short)
    {
        ofelia = SHORT_OFELIA;
    }
    else
    {
        ofelia = OFELIA;
    }

    println("");
    println(concat(concat(ofelia, ": "), text));
}

void speak_gertrudis(char *text, int is_short)
{
    char *gertrudis;

    if (is_short)
    {
        gertrudis = SHORT_GERTRUDIS;
    }
    else
    {
        gertrudis = GERTRUDIS;
    }

    println("");
    println(concat(concat(gertrudis, ": "), text));
}

void speak_jasmine(char *text, int is_short)
{
    char *jasmine;

    if (is_short)
    {
        jasmine = SHORT_JASMINE;
    }
    else
    {
        jasmine = JASMINE;
    }

    println("");
    println(concat(concat(jasmine, ": "), text));
}

void speak_scarecrown(char *text)
{
    char *character = SCARECROWN;
    println(concat(character, text));
}

void speak_tinman(char *text)
{
    char *character = TINMAN;
    println(concat(character, text));
}

void speak_lion(char *text)
{
    char *character = LION;
    println(concat(character, text));
}

void speak_toto(char *text)
{
    char *character = DOG;
    println(concat(character, text));
}