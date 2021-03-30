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
    char *err = "ERROR: the directory couldn't be accessed!\n";
    char *dir = getcwd( (char *) NULL, 0);

    if (dir == NULL)
    {
        write(2, err, strlen(err));
    } 
    else
    {
        strcat(dir, "\n");
        write(1, dir, strlen(dir));
        free(dir);
    }

    return (dir == NULL ? EXIT_FAILURE : EXIT_SUCCESS);
}

int main(int argc, char * argv[]) 
{
    pwd();
    return 0;
}