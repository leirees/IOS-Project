/**
 * @file exit.c
 * @author David Cuenca Marcos
 * @brief Exit command implementation.
 * @version 2
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/exit.h"

int exit_game()
{
    char *ans;
    bool exit_status = false;
 
    speak_charwtitle(&glinda, "Oh, my dear player, \nDo you really want to exit the game? [Y]es / [N]o, of course.", 0);
    scanf("%s", ans);

    if (!strncmp(ans, "y", 1) || !strncmp(ans, "Y", 1))
    {
        speak_charwtitle(&glinda, "Ok darling, have a nice day. See ya', dada!", 1);
        exit_status = true;
    }
    else if (!strncmp(ans, "n", 1) || !strncmp(ans, "N", 1))
    {
        speak_charwtitle(&glinda, "Well, let's play together! Let's go to hell!", 1);
    }
    else
    {
        char *err = THE_SYSTEM;
        speak_charwtitle(&ofelia, "You spoke wrongly, useless ape!", 0);
        printerr("Say something useful, you fool!", err);
        free(err);
    }

    return exit_status ? EXIT_SUCCESS : EXIT_FAILURE;
}