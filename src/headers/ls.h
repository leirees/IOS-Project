/**
 * @file ls.h
 * @author Zdravko Todorov, Team 2.2
 * @brief List directory header file.
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

#include "main_header.h"

//Used for handling directory files
#include <dirent.h>
//For stat system call for file attributes
#include <sys/stat.h>


/**
 * @brief List directory.
 * 
 * @param dir The directory 'to list'.
 * @param op_a -a option selected.
 * @param op_l -l option selected.
 */
void _ls(const char *dir, int op_a, int op_l);
