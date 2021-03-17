/**
 * @file exit.c
 * @author David Cuenca
 * @brief Exit, for shell.
 * @version 0.1
 * @date 2021-03-17
 * 
 * @copyright Copyright (c) 2021
 */

#include "../utilities.h"
#include "../colors.h"

char *_strcat(const char *dest, const char *src)
{
    unsigned long length = strlen(dest) + strlen(src);

    char *pointer = (char *)malloc(length);

    for (int i = 0; i < strlen(dest); i++)
    {
        pointer[i] = dest[i];
    }

    for (int i = 0; i < strlen(src); i++)
    {
        pointer[i + strlen(dest)] = src[i];
    }

    return pointer;
}

void print(const char *str, const char *color)
{
    char *dest = _strcat(_strcat(color, str), ANSI_COLOR_RESET);
    write(1, dest, strlen(dest));
}

/**
 * @brief Main body of the program.
 * 
 * @param argc 
 * @param argv 
 * @return int 0 iff ok.
 */
int main(int argc, char *argv[])
{
    print("Do you really want to exit the game? \n", ANSI_COLOR_RESET);
    print("OK, good for me!\n", ANSI_COLOR_RESET);

    // String manipulation to add yellow color.
    // print("BYE!!\n", ANSI_COLOR_YELLOW);
    exit(0);
}