/**
 * @file pwd.c
 * @author David Cuenca 
 *
 * @brief Asks for help to know where the main character is.
 *
 * @version 0.1
 * @date 2021-03-16
 * 
 * @copyright Copyright (c) 2021
 */

// Utilities to deal with files, directories.
#include "../utilities.h"
// Colors for printing.
#include "../colors.h"

/**
 * @brief Reads and writes the directory route to stdout.
 * 
 * @return int 1 if error; else 0.
 */
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

    return (dir == NULL ? ERROR : SUCCESS);
}

/**
 * @brief Main loop of the program.
 * 
 * @param argc argument counter.
 * @param argv argument vector.
 * @return int 0 iff ok.
 */
int main(int argc, char * argv[]) 
{
    pwd();
    return 0;
}