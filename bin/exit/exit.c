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
// #include "../string.h"

// TODO: use ../string.h
char *_strcat(const char *dest, const char *src)
{
    char *pointer = (char *) malloc((sizeof(dest) + sizeof(src)) / sizeof(char));
    for (int i = 0; i < strlen(dest); i++) {
        pointer[i] = dest[i];
    }

    for (int i = 0; i < strlen(src); i++) {
        pointer[i + strlen(dest)] = src[i];
    }

    return pointer;
}

void print(const char * str, const char *color) 
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
int main(int argc, char * argv[])
{
    const char *exitarn = "Do you really want to exit this wonderful world? :D";
    const char *noIdont = "OK, good for me!";
    const char *exitmsg = "BYE!!\n";

    // String manipulation to add yellow color.
    print(exitmsg, ANSI_COLOR_YELLOW);
    exit(0);
}