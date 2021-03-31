/**
 * @file cd.h
 * @author Mikel Aristu
 * @brief Utilities to deal with files, directories.
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

/**
 * @brief Change of directory.
 * 
 * @param path Path to the new directory.
 */
void _cd(char *path);

/**
 * @brief Change of directory, from current process.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
extern int cd(int argc, const char *argv[]);

