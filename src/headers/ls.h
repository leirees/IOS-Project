/**
 * @file ls.h
 * @author ...
 * @brief ...
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

//Used for basic input/output stream
#include <stdio.h>

//Used for handling directory files
#include <dirent.h>

//For EXIT codes and error handling
#include <errno.h>
#include <stdlib.h>

//For stat system call for file attributes
#include <sys/stat.h>

//For write system call
#include <unistd.h>

//For string concatenation
#include <string.h>

/**
 * @brief List directory.
 * 
 * @param dir ...
 * @param op_a ...
 * @param op_l ...
 */
void _ls(const char *dir, int op_a, int op_l);