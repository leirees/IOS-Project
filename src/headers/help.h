/**
 * @file help.h
 * @author ...
 * @brief ...
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

//For write system call
#include <unistd.h>

//Used for basic input/output stream
#include <stdio.h>

//Standart library
#include <stdlib.h>
#include <sys/uio.h>

//For string concatenation
#include <string.h>

/**
 * @brief Help command.
 * 
 * @param command Command to get help about.
 * @param op_d ...
 * @param op_m ...
 * @param op_s ...
 */
void _help(const char *command, int op_d, int op_m, int op_s);
