/**
 * @file grep.h
 * @author ...
 * @brief ...
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

//Defines flags for open and related library functions
#include <fcntl.h>

//For write system call
#include <unistd.h>

//Used for basic input/output stream
#include <stdio.h>

//Standart library
#include <stdlib.h>
#include <sys/uio.h>

//For string concatenation
#include <string.h>

#define O_RDONLY 00    //Define the flag