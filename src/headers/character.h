#include "libstring.h"

typedef struct
{
    char *name;
    __INT8_TYPE__ is_with_you;
} character;

/**
 * @brief Makes the character speak.
 * 
 * @param c The character.
 * @param text The text.
 */
void speak(character *c, char *text);