/**
 * @file cd.c
 * @author Mikel Aristu, David Cuenca Marcos
 * @brief Utilities to deal with files, directories.
 * @version 2
 * @date 2021-04-16
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/cd.h"

int cd(char *path)
{
    if (!strcmp("", path))
    {
        // If the command is used incorrectly, it will teach the user how to use it.
        printerr("Usage: cd directory");
    }

    DIR *dh = opendir(path);

    if (!dh)
    {
        if (errno = ENOENT)
        {
            //If the directory is not found.
            printerr("Directory doesn't exist");
        }
        else
        {
            //If the directory is not readable, then throw error and exit.
            printerr("Unable to read directory");
        }

        return EXIT_FAILURE;
    }
    else
    {
        chdir(path);
    } 

    return EXIT_SUCCESS;
}