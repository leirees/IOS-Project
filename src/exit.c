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

int main(int argc, char *argv[])
{
    char ans;

    do
    {
        // Ask user to confirm [Y]/[N]:
        println("Do you really want to exit the game? [Y] / [N]");
        scanf("%c", &ans);
        
        if (ans == 'N' || ans == 'n') 
        {
            println(concat(ANSI_COLOR_RED, "OK, good for me! Let's go to hell"));
            return EXIT_SUCCESS;
        }
        else if (ans == 'Y' || ans == 'y')
        {
            println(concat(ANSI_COLOR_YELLOW, "BYE!! Have a nice day :D "));
            kill(getppid(), SIGKILL);
            exit(EXIT_SUCCESS);
        }
        else
        {
            printerr("Anserror!! Say something useful, you fool");
            print(ANSI_COLOR_RESET);
        }
    } while(1);

    return EXIT_FAILURE;
}