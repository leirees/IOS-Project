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
#include "headers/libstring/libstring.h"

#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

int cd(char *path)
{
    char *err_title = THE_SYSTEM;
    char *glinda = GLINDA;

    if (chdir((const char *)path) == -1)
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
        
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}