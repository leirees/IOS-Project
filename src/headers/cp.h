/**
 * @file cp.h
 * @author ...
 * @brief ...
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

/**
 * @brief Go to path. Change directory.
 * 
 * @param path Path to the new directory.
 * @return int 1 iff success, 0 otherwise.
 */
extern int cd(char *path);