/**
 * @file exit.c
 * @author David Cuenca Marcos
 * @brief Exit command implementation.
 * @version 0.1
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/exit.h"

int exit_game()
{
    char *ans;
    speak_glinda("Oh, my dear player, \nDo you really want to exit the game? [Y]es / [N]o, of course.", 0);
    scanf("%s", &ans);
    
    if (!strcmp(ans, "y") || !strcmp(ans, "Y"))
    {
        speak_glinda("Ok darling, have a nice day. See ya', dada!", 1);
        _exit(127);
    }
    else if (!strcmp(ans, "n") || !strcmp(ans, "N"))
    {
        speak_glinda("Well, let's play together! Let's go to hell!", 1);
    }
    else
    {
        printerr("Say something useful, you fool!");
        speak_ofelia("You spoke wrongly, useless ape!", 0);
    }

    return EXIT_FAILURE;
}