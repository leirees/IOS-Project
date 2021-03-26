/**
 * @file string.h
 * @author David Cuenca Marcos
 * @brief Modified string library header.
 * @version 0.1
 * @date 2021-03-26
 * 
 * @copyright Copyright (c) 2021
 */
#include <string.h>

/**
 * @brief Concat two string.
 * 
 * @param str1 First str to concat.
 * @param str2 Second str to concat.
 * @return char* str1 + str2.
 */
char * concat(char * str1, char * str2);

/**
 * @brief Print a string, without an ending char implicit.
 * 
 * @param str String to print.
 */
void print(char * str);

/**
 * @brief Print a string, with an implicit \n at the end of the string.
 * 
 * @param str String to print.
 */
void println(char * str);