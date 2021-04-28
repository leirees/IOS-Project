#include "libstring.h"

// The Three Knights of the Player + DOG
#define SCARECROWN underlined(bold("The Brainless Scarecrown"));
#define TINMAN underlined(bold("The Heartless Tinman"));
#define LION underlined(bold("The Coward Lion"));

// This is Toto, you fellow dog :DD
#define DOG underlined(concat(concat(ANSI_COLOR_WHITE, bold("Toto")), ANSI_COLOR_RESET));