/**
 * @file pwd.c
 * @author David Cuenca 
 * @brief Asks for help to know where the main character is.
 * @version 0.1
 * @date 2021-03-16
 * 
 * @copyright Copyright (c) 2021
 */

#include <unistd.h>
#include <string.h>

/**
 * @brief Writes the current path from root, of the user.
 * 
 * @return int 1 iff error.
 */
int pwd()
{
    // Inside the game, it is impossible to have a directory without permissions to read but to access.
    char *res = getcwd((char *)NULL, 0);
    write(1, res, strlen(res));
    write(1, "\n", 1);

    return 0;
}

int main(int argc, char *argv[])
{
    return pwd();
}