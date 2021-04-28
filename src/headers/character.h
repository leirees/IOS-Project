#include "libstring.h"

typedef struct
{
    char *name;
    unsigned char has_magic;
    unsigned char is_evil;
    unsigned char is_neutral;
    unsigned char is_with_you;
    unsigned char is_dead;
} character;

/**
 * @brief Create a character object
 * 
 * @param c Character object (struct).
 * @param name The name of the character.
 * @param has_magic If the character has some kind of magic, 1; else 0.
 * @param is_evil If the character is evil, 1; else, 0.
 * @param is_neutral If the character is neutral, is evil is inactivated. If is_neutral 1, neutral; else, 0.
 * @param is_with_you If the character is with you, 1; else, 0.
 */
void create_character(character *c, char *name, unsigned char has_magic, unsigned char is_evil, unsigned char is_neutral, unsigned char is_with_you);

/**
 * @brief Makes the character speak.
 * 
 * @param c The character.
 * @param text The text.
 */
void speak_character(character *c, char *text);