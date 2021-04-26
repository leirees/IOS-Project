#include "character.h"

/**
 * @brief A brief definition of a character with title.
 */
typedef struct
{
    unsigned char is_evil;
    char *short_title;
    char *real_title;
} character_with_title;

/**
 * @brief The character speaks.
 * 
 * @param str The text she says.
 * @param is_title_short If the title is short (1) or not (0).
 */
void speak(character_with_title *someone, char *text, unsigned char is_title_short);