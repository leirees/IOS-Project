/**
 * @file cd.h
 * @author Mikel Aristu
 * @brief Utilities to deal with files, directories.
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

#include "main_header.h"

#include <dirent.h>
#include <errno.h>

/**
 * @brief Change of directory, from current process.
 * 
 * @param path The path of the directory to go.
 * @return int 0 iff success
 */
extern int cd(char *path);
