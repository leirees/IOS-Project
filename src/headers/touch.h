/**
 * @file touch.h
 * @author Mikel Aristu
 * @brief Headers for touch command.
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

#include "main_header.h"

#include <sys/stat.h>
#include <fcntl.h>

/**
* @brief This void method will call to the open function. In case of error, the open system call will return -1 and an error message will appear.
*
* @param f_name that will be the wanted file name to be created.
* @return int 1 iff failure.
*/
int touch(char *f_name);