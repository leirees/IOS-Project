/**
 * @file touch.h
 * @author Mikel Aristu
 * @brief Headers for touch command.
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/**
* @brief This void method will call to the open function. In case of error, the open system call will return -1 and an error message will appear.
* @param f_name that will be the wanted file name to be created.
* @param flags that will be the flags of the system call.
* @param modes that will be the permissions of the file created.
*/
void _touch(char *f_name, char flags, int modes);