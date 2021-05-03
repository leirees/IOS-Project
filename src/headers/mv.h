/**
 * @file mv.h
 * @author Mikel Aristu, Team 2.2
 * @brief Headers for mv command.
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */
#include "main_header.h"
// To deal with directories.
#include <dirent.h>
// To deal with errors.
#include <errno.h>

/**
 * @brief Explain the user how to use the command.
 * 
 */
void howToUse();

/**
 * @brief Move one file from "origin" to "end".
 * 
 * @param origin_file The original path of the file.
 * @param end_file The end destinations of the file.
 * @return int 1 iff failure.
 */
int mv(char *origin_file, char *end_file);
