#include "character.h"

/**
 * @brief A brief definition of a character with title.
 */
typedef struct
{
    character *cwtitle;
    char *short_title;
    char *long_title;
} character_with_title;

/**
 * @brief Create a character object
 * 
 * @param c Character object (struct).
 * @param name The name of the character.
 * @param short_title The short title of the character.
 * @param long_title The long title of the character.
 * @param has_magic If the character has some kind of magic, 1; else 0.
 * @param is_evil If the character is evil, 1; else, 0.
 * @param is_neutral If the character is neutral, is evil is inactivated. If is_neutral 1, neutral; else, 0.
 * @param is_with_you If the character is with you, 1; else, 0.
 */
void create_charwtitle(character_with_title *c, char *name, char *short_title, char *long_title, unsigned char has_magic, unsigned char is_evil, unsigned char is_neutral, unsigned char is_with_you);

/**
 * @brief The character speaks.
 * 
 * @param c The character with title.
 * @param str The text she says.
 * @param is_title_short 1, if the title is short; else, 0.
 */
void speak_charwtitle(character_with_title *c, char *text, unsigned char is_title_short);