#include "libstring.h"

// The four witcher talk
#define GLINDA underlined(concat(concat(concat(ANSI_COLOR_CYAN, bold("Glinda")), ", \"The Good Witch of the NORTH\""), ANSI_COLOR_RESET));
#define SHORT_GLINDA underlined(concat(concat(ANSI_COLOR_CYAN, bold("Glinda")), ANSI_COLOR_RESET));
#define OFELIA underlined(concat(concat(concat(ANSI_COLOR_RED, bold("Ofelia")), ", \"The Most Evil Bad Witch, The Witch of the WEST\""), ANSI_COLOR_RESET));
#define SHORT_OFELIA underlined(concat(concat(concat(ANSI_COLOR_RED, bold("Ofelia")), ", \"The Most Evil Bad Witch\""), ANSI_COLOR_RESET));
#define GERTRUDIS underlined(concat(concat(concat(ANSI_COLOR_YELLOW, bold("Gertrudis")), ", \"The Evil Witch of the EAST\""), ANSI_COLOR_RESET));
#define SHORT_GERTRUDIS underlined(concat(concat(ANSI_COLOR_YELLOW, bold("Gertrudis")), ANSI_COLOR_RESET));
#define JASMINE underlined(concat(concat(concat(ANSI_COLOR_GREEN, bold("Jasmine")), ", \"The Good Witch of the SOUTH\""), ANSI_COLOR_RESET));
#define SHORT_JASMINE underlined(concat(concat(ANSI_COLOR_GREEN, bold("Jasmine")), ANSI_COLOR_RESET));