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
#include "headers/characters/character.h"

int cd(char *path)
{
    char *err_title = THE_SYSTEM;
    char *glinda = GLINDA;

    char *directory_path;

    if (!strcmp("", path))
    {
        // If the directory field is empty,
        // go to the root directory.
        directory_path = root_dir;
    }
    else
    {
        directory_path = path;
    }

    DIR *dh = opendir(path);

    if (dh == NULL)
    {
        // If the directory is not found.
        if (errno = ENOENT)
        {
            printerr("No DIR found. %ERROR!", err_title);
            speak_character(glinda, "It look like that place you mean doesn't exist, my dear sweet child.");
            speak_character(glinda, "You'd better apply in you Geography lectures, if you don't want to loose yourself.");
        }
        else
        {
            // If the directory is not readable, then throw error and exit.
            printerr("No DIR found. %ERROR!\n Revise your internal configuration, player.", err_title);
        }

        free(err_title);
        free(glinda);
        return EXIT_FAILURE;
    }

    // Then, if the directory is closed, we can change of dir.
    closedir(dh);

    // Change of dir,
    chdir((const char *)directory_path);

    free(glinda);
    free(err_title);
    return EXIT_SUCCESS;
}