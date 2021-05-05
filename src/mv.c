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
#include <sys/fcntl.h>
#include <sys/stat.h>

int mv(char *origin_file, char *end_file)
{
    return link((const char *)origin_file, (const char *)end_file) || unlink((const char *)origin_file) ? EXIT_FAILURE : EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    char *err_sys = THE_SYSTEM;
    char *glinda = GLINDA;

    if (argc == 3)
    {
        if (mv(argv[1], argv[2]))
        {
            // If there is no directory to reach,
            printerr("I cannot reach that place, ape. Move on!", err_sys);
            printerr("I cannot move there!", err_sys);
            
            _exit(EXIT_FAILURE);
        }
        _exit(EXIT_SUCCESS);
    }

    // If the command is used incorrectly, it will teach the user how to use it.
    printerr("HAHAHAHAHAHA, useless ape!", err_sys);
    speak_character(glinda, "My dear sweet child, do <<mv file.txt new_location>>, please :)");

    _exit(EXIT_FAILURE);
}