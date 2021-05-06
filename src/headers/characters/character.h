/* SYSTEM definition, for error messages inside the game (for the player) */
#define THE_SYSTEM underlined(concat(reversed(concat(ANSI_COLOR_RED, "THE SYSTEM")), ANSI_COLOR_RESET));

// The player
#define PLAYER underlined(concat(concat(ANSI_COLOR_WHITE, bold("The Player")), ANSI_COLOR_RESET));

// Definition of THE WITCHES
// The four witches' titles
#define GLINDA_NAME "Glinda"
#define GLINDA_TITLE ", <<The Good Witch of the NORTH>>"
#define GLINDA_COMPLETE concat(BOLD, underlined(concat(ANSI_COLOR_CYAN, concat(GLINDA_NAME, GLINDA_TITLE))))
#define GLINDA GLINDA_COMPLETE
#define SHORT_GLINDA concat(BOLD, underlined(concat(ANSI_COLOR_CYAN, GLINDA_NAME)))

#define OFELIA_NAME "Ofelia"
#define OFELIA_TITLE ", <<The Most Evil Bad Witch, The Witch of the WEST>>"
#define OFELIA_COMPLETE concat(BOLD, underlined(concat(ANSI_COLOR_RED, concat(OFELIA_NAME, OFELIA_TITLE))))
#define OFELIA OFELIA_COMPLETE
#define SHORT_OFELIA concat(BOLD, underlined(concat(ANSI_COLOR_RED, concat(OFELIA_NAME, ", <<The Most Evil Bad Witch>>"))))

#define GERTRUDIS_NAME "Gertrudis"
#define GERTRUDIS_TITLE ", <<The Evil Witch of the EAST>>"
#define GERTRUDIS_COMPLETE concat(BOLD, underlined(concat(ANSI_COLOR_YELLOW, concat(GERTRUDIS_NAME, GERTRUDIS_TITLE))))
#define GERTRUDIS GERTRUDIS_COMPLETE
#define SHORT_GERTRUDIS concat(BOLD, underlined(concat(ANSI_COLOR_YELLOW, GERTRUDIS_NAME)))

#define JASMINE_NAME "Jasmine"
#define JASMINE_TITLE ", <<The Good Witch of the SOUTH>>"
#define JASMINE_COMPLETE concat(BOLD, underlined(concat(ANSI_COLOR_GREEN, concat(JASMINE_NAME, JASMINE_TITLE))))
#define JASMINE JASMINE_COMPLETE
#define SHORT_JASMINE concat(BOLD, underlined(concat(ANSI_COLOR_GREEN, GERTRUDIS_NAME)))

/* Definition of the COMPANIONS */
// The Three Knights of the Player + DOG
#define SCARECROWN underlined(bold("The Brainless Scarecrown"))
#define TINMAN underlined(bold("The Heartless Tinman"))
#define LION underlined(bold("The Coward Lion"))

// This is Toto, you fellow dog :DD
#define DOG concat(BOLD, underlined("TOTO <<My doge>>"))

/* Definition of EXTRAS */
#define TREES concat(BOLD, underlined("Forest trees"))
#define GUARDIAN concat(BOLD, underlined("Guardian"))
#define GHOST concat(BOLD, underlined("CASPER <<The Friendly Ghost>>"))
#define ADMIN concat(BOLD, underlined("THE ADMIN"))

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
    char *name;
    char *short_title;
    char *long_title;
    unsigned char has_magic;
    unsigned char is_evil;
    unsigned char is_with_you;
    unsigned char is_dead;
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
void speak_character(char *title, char *text);