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
    char *err_title = THE_SYSTEM;

    if (!strcmp("", path))
    {
        // If the directory field is empty,
        cd(root_dir);
        return EXIT_SUCCESS;
    }

    DIR *dh = opendir(path);

    if (!dh)
    {
        // If the directory is not found.
        if (errno = ENOENT)
        {
            printerr("No DIR found. %ERROR!", err_title);
            speak_charwtitle(&glinda, "It look like that place you mean doesn't exist, my dear sweet child. You'd better apply in you Geography lectures, if you don't want to loose yourself.", 0);
        }
        else
        {
            // If the directory is not readable, then throw error and exit.
            printerr("No DIR found. %ERROR!\n Revise your internal configuration, player.", err_title);
        }
        
        free(err_title);
        return EXIT_FAILURE;
    }
    else
    {
        if (closedir(dh) < 0)
        {
            // If the directory cannot bet closed.
            speak_charwtitle(&glinda, "It look like that place you mean doesn't exist, my dear sweet child. You'd better apply in you Geography lectures, if you don't want to loose yourself.", 0);
            free(err_title);
            return EXIT_FAILURE;
        }

        // Then, if the directory is closed, we can change of dir.
        chdir((const char *) path);
    }

    return EXIT_SUCCESS;
}