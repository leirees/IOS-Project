#include "../libstring/libstring.h"

/* SYSTEM definition, for error messages inside the game (for the player) */
#define THE_SYSTEM underlined(concat(reversed(concat(ANSI_COLOR_RED, "THE SYSTEM")), ANSI_COLOR_RESET));

// The player
#define PLAYER underlined(concat(concat(ANSI_COLOR_WHITE, bold("The Player")), ANSI_COLOR_RESET));

// Definition of THE WITCHES
// The four witches' titles
#define GLINDA underlined(concat(concat(concat(ANSI_COLOR_CYAN, bold("Glinda")), ", \"The Good Witch of the NORTH\""), ANSI_COLOR_RESET));
#define SHORT_GLINDA underlined(concat(concat(ANSI_COLOR_CYAN, bold("Glinda")), ANSI_COLOR_RESET));
#define OFELIA underlined(concat(concat(concat(ANSI_COLOR_RED, bold("Ofelia")), ", \"The Most Evil Bad Witch, The Witch of the WEST\""), ANSI_COLOR_RESET));
#define SHORT_OFELIA underlined(concat(concat(concat(ANSI_COLOR_RED, bold("Ofelia")), ", \"The Most Evil Bad Witch\""), ANSI_COLOR_RESET));
#define GERTRUDIS underlined(concat(concat(concat(ANSI_COLOR_YELLOW, bold("Gertrudis")), ", \"The Evil Witch of the EAST\""), ANSI_COLOR_RESET));
#define SHORT_GERTRUDIS underlined(concat(concat(ANSI_COLOR_YELLOW, bold("Gertrudis")), ANSI_COLOR_RESET));
#define JASMINE underlined(concat(concat(concat(ANSI_COLOR_GREEN, bold("Jasmine")), ", \"The Good Witch of the SOUTH\""), ANSI_COLOR_RESET));
#define SHORT_JASMINE underlined(concat(concat(ANSI_COLOR_GREEN, bold("Jasmine")), ANSI_COLOR_RESET));

/* Definition of the COMPANIONS */
// The Three Knights of the Player + DOG
#define SCARECROWN underlined(bold("The Brainless Scarecrown"));
#define TINMAN underlined(bold("The Heartless Tinman"));
#define LION underlined(bold("The Coward Lion"));

// This is Toto, you fellow dog :DD
#define DOG underlined(concat(concat(ANSI_COLOR_WHITE, bold("Toto")), ANSI_COLOR_RESET));

/* Definition of EXTRAS */
#define TREES underlined(bold("Forest trees"))
#define GUARDIAN underlined(bold("Guardian"))
#define GHOST underlined(bold("Ghost"))
#define ADMIN underlined(bold("ADMIN"))

typedef struct
{
    char *name;
    unsigned char is_dead;
    unsigned char fails;
    unsigned int score;
} player;

/**
 * @brief Create a player object.
 * 
 * @param p The player.
 * @param name The name of the player.
 */
extern void create_player(player *p, char *name);

/* Definition of generic CHARACTER object */
typedef struct
{
    char *name;
    unsigned char has_magic;
    unsigned char is_evil;
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
 * @param is_with_you If the character is with you, 1; else, 0.
 */
void create_character(character *c, char *name, unsigned char has_magic, unsigned char is_evil, unsigned char is_with_you);

/* Definition of generic CHARACTERS WITH TITLES */
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
void create_charwtitle(character_with_title *c, char *name, char *short_title, char *long_title, unsigned char has_magic, unsigned char is_neutral, unsigned char is_with_you);

/**
 * @brief Create a witch object
 * 
 * @param c The character with title that will hold the witch entity.
 * @param name The name of the witch.
 * @param short_title Her "short title".
 * @param long_title Her "complete title".
 * @param is_evil 1 iff the witch is evil.
 */
void create_witch(character_with_title *c, char *name, char *short_title, char *long_title, unsigned char is_evil);

/**
 * @brief Makes the character speak.
 * 
 * @param c The character.
 * @param text The text.
 */
void speak_character(const char *title, char *text);