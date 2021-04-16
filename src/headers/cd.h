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

#include "libstring.h"

/**
 * @brief Change of directory, from current process.
 * 
 * @param path The path of the directory to go.
 * @return int 0 iff success
 */
extern int cd(char *path);

