/**
 * @file pwd.c
 * @author David Cuenca 
 * @brief Asks for help to know where the main character is.
 * @version 0.1
 * @date 2021-03-16
 * 
 * @copyright Copyright (c) 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * @brief Reads and writes the directory route to stdout.
 * 
 * @return int 1 if error; else 0.
 */
int pwd();