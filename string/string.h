/**
 * @file string.h
 * @author David Cuenca Marcos
 * 
 * @brief Advanced string library, based on Unix syscalls and string.h lib.
 * Based on high-level (over C) string utilitiies.
 * 
 * @version 1
 * @date 2021-03-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define ANSI_COLOR_RESET   "\x1b[0m"

/**
 * @brief Concatenates two strings and returns a pointer to the
 * concat of both.
 * 
 * @param str1 First string to concat. Beginning of the new string.
 * @param str2 Second string to concat. End of the new string.
 * @return char* Concat. string, as char[].
 */
char *concat(char * str1, char * str2);

/**
 * @brief Print a string in stdout.
 * 
 * @param str String to print.
 */
void print(char *str);

/**
 * @brief Print a string in stdout, with linescape.
 * 
 * @param str 
 */
void println(char *str);