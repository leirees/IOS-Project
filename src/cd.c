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
        println("Glinda, \"The good witch from the North\": Remember, player, you should always ");
        println("teleport when pronounce << cd \"the place you want to go\" >>. ");
        println("Glinda, \"The good witch from the North\": That is something you learn in 1st course ");
        println("in the Wizardry School, my little fool.");
    }

    DIR *dh = opendir(path);

    if (!dh)
    {
        if (errno = ENOENT)
        {
            //If the directory is not found.
            printerr("Glinda, \"The good witch from the North\": It look like that place you mean doesn't exist, my dear sweet child.");
            println("Glinda, \"The good witch from the North\": You'd better apply in you Geography lectures, if you don't want to loose yourself.");
        }
        else
        {
            //If the directory is not readable, then throw error and exit.
            printerr("Glinda, \"The good witch from the North\": Oh, sweet player, this is nasty! You should revise it. Please, do it.");
        }

        return EXIT_FAILURE;
    }
    else
    {
        if (closedir(dh) < 0)
        {
            // If the directory cannot bet closed.
            printerr("Glinda, \"The good witch from the North\": It look like that place you mean doesn't exist, my dear sweet child.");
            println("Glinda, \"The good witch from the North\": You'd better apply in you Geography lectures, if you don't want to loose yourself.");
            return EXIT_FAILURE;
        }

        // Then, if the directory is closed, we can change of dir.
        chdir(path);
    }

    return EXIT_SUCCESS;
}