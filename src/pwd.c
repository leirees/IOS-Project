/**
 * @file pwd.c
 * @author David Cuenca 
 * @brief Asks for help to know where the main character is.
 * @version 0.1
 * @date 2021-03-16
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/pwd.h"

int pwd()
{   
    char *dir = getcwd( (char *) NULL, 0);

    if (dir == NULL)
    {
        printerr("ERROR: the directory couldn't be accessed!\n");
    } 
    else
    {
        println(dir);
        free(dir);
    }

    return (dir == NULL ? EXIT_FAILURE : EXIT_SUCCESS);
}

int main(int argc, char * argv[]) 
{
    pwd();
    return 0;
}