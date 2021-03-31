/**
 * @file cd.c
 * @author Mikel Aristu
 * @brief Utilities to deal with files, directories.
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/cd.h"

void _cd(char *path) 
{
    chdir(path);
    write(1, "changed", strlen("changed"));
    printf("\n");
}

int cd(int argc, const char *argv[])
{
    if (argc == 2)
    {
        // Try to open the directory written
        DIR *dh = opendir(argv[1]);

        if (argv[1] == "..")
        {
            // Go back to the previous directory.
           _cd("..");

        }
        else if (argv[1] == "."){
            //Print the current directory.
            write(2, "asd", 3);
        }
        else if (!dh)
        {
            if (errno = ENOENT)
            {
                //If the directory is not found.
                perror("Directory doesn't exist");
            }
            else
            {
                //If the directory is not readable then throw error and exit.
                perror("Unable to read directory");
            }
            exit(EXIT_FAILURE);
        }
        else
        {
            //Go on to the written directory.
            _cd(readdir(dh)->d_name);
        }
    }
    else
    {
        // If the command is used incorrectly, it will teach the user how to use it.
        write(2, "Usage: cd directory\n", 19);
        printf("\n");
    }
}