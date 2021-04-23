#include "character.h"

// The Three Knights of the Player
#define SCARECROWN underlined(bold("The Brainless Scarecrown"));
#define TINMAN underlined(bold("The Heartless Tinman"));
#define LION underlined(bold("The Coward Lion"));
#define DOG underlined(concat(concat(ANSI_COLOR_WHITE, bold("Toto")), ANSI_COLOR_RESET));

static character scarecrown;
static character tinman;
static character lion;
static character dog;

extern void create_scarecrown();

extern void create_tinman(__INT8_TYPE__ is_with_you);

extern void create_lion();

extern void create_dog();

extern void kill_dog();

/**
 * @brief Speak Scarecrown.
 * 
 * @param text What it says.
 */
extern void speak_scarecrown(char *text);

/**
 * @brief Speak Tinman.
 * 
 * @param text What he says.
 */
extern void speak_tinman(char *text);

/**
 * @brief Speak Lion.
 * 
 * @param text What he says.
 */
extern void speak_lion(char *text);

/**
 * @brief Speak Toto.
 * 
 * @param text "Woof, woof :)".
 */
extern void speak_toto(char *text);