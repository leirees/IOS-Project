/**
 * @file pwd.c
 * @author David Cuenca 
 * @brief Asks for help to know where the main character is.
 * @version 0.1
 * @date 2021-03-16
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/libstring/libstring.h"

#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Writes the current path from root, of the user.
 * 
 * @return int 1 iff error.
 */
int pwd()
{
    // Inside the game, it is impossible to have a directory without permissions to read but to access.
    println(getcwd((char *)NULL, 0));
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    _exit(pwd() ? EXIT_FAILURE : EXIT_SUCCESS);
}