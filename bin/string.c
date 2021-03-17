#include "string.h"

char *_strcat(char *dest, const char *src)
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