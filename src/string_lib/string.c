#include "string.h"

char * concat(char * str1, char * str2)
{
    unsigned int result_length = strlen(str1) + strlen(str2);
    char * result = (char *) malloc(result_length);

    for (unsigned int i = 0; i < strlen(str1); i++) 
    {
        result[i] = str1[i];
    }

    for (unsigned int i = 0; i < strlen(str2); i++) 
    {
        result[i + strlen(str1)] = str2[i];
    }

    return result;
}