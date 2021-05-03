/**
 * @file mv.c
 * @author Mikel Aristu, Team 2.2
 * @brief The command used to move a file to a different location.
 * @version 0.1
 * @date 2021-03-26
 *
 * @copyright Copyright (c) 2021
 */

#include "headers/mv.h"
#include "headers/characters/character.h"

void howToUse()
{
    printf("Usage:\n mv file.txt new_location\n");
    exit(1);
}

int mv(char *origin_file, char *end_file)
{
    struct dirent *name_file;

    char *err_title = THE_SYSTEM;
    char *this_dir;

    /* 1- Try to open the directory */
    DIR *end = opendir(end_file);

    if (end == NULL)
    {
        if (errno == ENOENT)
        {
            // If there is no directory to reach,
            printerr("I cannot reach that place, ape. Move on!", err_title);
        }
        else
        {
            // If the directory cannot be opened,
            printerr("I cannot go to that place, ape. Move on!", err_title);   
        }

        printerr("I cannot move there!", err_title);
        _exit(EXIT_FAILURE);
    }

    /* 2- Try to move the file, from "origin" to "end" */
    // TODO: edit this part. Not working properly.
    name_file = readdir(end);
    
    // Get the current directory path. Never NULL.
    this_dir = getcwd((char *)NULL, 0);

    // Attach mv location to path && keep original file name
    char *res = concat(concat(concat(concat(this_dir, "/"), end_file), "/"), origin_file);

    bool not_success = false;

    if (rename(origin_file, name_file->d_name) == -1)
    {
        printerr("Error: directory not found!", err_title);
        not_success = true;
    }

    closedir(end);
    return not_success ? EXIT_FAILURE : EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        char *origin_file = argv[1];
        char *end_file = argv[2];
        _exit(mv(origin_file, end_file) ? EXIT_FAILURE : EXIT_SUCCESS);
    }
    else
    {
        // If the command is used incorrectly, it will teach the user how to use it.
        howToUse();
        _exit(EXIT_FAILURE);
    }
}