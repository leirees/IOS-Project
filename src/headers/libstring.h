/**
 * @file string.h
 * @author David Cuenca Marcos
 * @brief Modified string library header.
 * @version 0.1
 * @date 2021-03-26
 * 
 * @copyright Copyright (c) 2021
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// COLORS in ANSI, for Terminal coloring
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_WHITE    "\x1b[37m"
#define ANSI_COLOR_RESET    "\x1b[0m"

// BOLD text
#define BOLD                "\x1b[1m"
#define NO_BOLD             "\x1b[0m"

// UNDERLINE text
#define UNDERLINE           "\x1b[4m"
#define NO_UNDERLINE        "\x1b[0m"

// REVERSE background, text color
#define REVERSE             "\x1b[7m"
#define NO_REVERSE          "\x1b[0m"

// The four witcher talk
#define GLINDA          underlined(concat(concat(concat(ANSI_COLOR_CYAN, bold("Glinda")), ", \"The Good Witch of the NORTH\""), ANSI_COLOR_RESET));
#define SHORT_GLINDA    underlined(concat(concat(ANSI_COLOR_CYAN, bold("Glinda")), ANSI_COLOR_RESET));
#define OFELIA          underlined(concat(concat(concat(ANSI_COLOR_RED,  bold("Ofelia")), ", \"The Most Evil Bad Witch, The Witch of the WEST\""), ANSI_COLOR_RESET));  
#define SHORT_OFELIA    underlined(concat(concat(concat(ANSI_COLOR_RED,  bold("Ofelia")), ", \"The Most Evil Bad Witch\""), ANSI_COLOR_RESET));  
#define GERTRUDIS       underlined(concat(concat(concat(ANSI_COLOR_YELLOW, bold("Gertrudis")), ", \"The Evil Witch of the EAST\""), ANSI_COLOR_RESET));
#define SHORT_GERTRUDIS underlined(concat(concat(ANSI_COLOR_YELLOW, bold("Gertrudis")), ANSI_COLOR_RESET));
#define JASMINE         underlined(concat(concat(concat(ANSI_COLOR_GREEN, bold("Jasmine")), ", \"The Good Witch of the SOUTH\""), ANSI_COLOR_RESET));
#define SHORT_JASMINE   underlined(concat(concat(ANSI_COLOR_GREEN, bold("Jasmine")), ANSI_COLOR_RESET));

// The Three Knights of the Player
#define SCARECROWN      underlined(bold("The Brainless Scarecrown"));
#define TINMAN          underlined(bold("The Heartless Tinman"));
#define LION            underlined(bold("The Coward Lion"));

// The player
#define PLAYER          underlined(concat(concat(ANSI_COLOR_WHITE, bold("The Player")), ANSI_COLOR_RESET));
#define DOG             underlined(concat(concat(ANSI_COLOR_WHITE, bold("Toto")), ANSI_COLOR_RESET));

// System
#define THE_SYSTEM      underlined(concat(reversed(concat(ANSI_COLOR_RED, "THE SYSTEM")), ANSI_COLOR_RESET));

/**
 * @brief Concat two string.
 * 
 * @param str1 First str to concat.
 * @param str2 Second str to concat.
 * @return char str1 + str2.
 */
extern char *concat(char *str1, char *str2);

/**
 * @brief Print a string, without an ending char implicit.
 * 
 * @param str String to print.
 */
extern void print(char *str);

/**
 * @brief Print a string, with an implicit \n at the end of the string.
 * 
 * @param str String to print.
 */
extern void println(char *str);

/**
 * @brief Print an error message.
 * 
 * @param str Error msg.
 */
extern void printerr(char *str);

/**
 * @brief Set a string as bold text.
 * 
 * @param str The text to bold.
 * @return char* The text "bolded".
 */
extern char *bold(char *str);

/**
 * @brief Set a string as underlined.
 * 
 * @param str The text to underline.
 * @return char* The text underlined.
 */
extern char *underlined(char *str);

/**
 * @brief Set a text reversed.
 * 
 * @param str The text, to reverse in color.
 * @return char* The text, reversed in color.
 */
extern char *reversed(char *str);

/**
 * @brief Speak Glinda, The Good Witch of the NORTH.
 * 
 * @param text What she says.
 * @param is_short If Glinda's titles should be shortened.
 */
extern void speak_glinda(char *text, int is_short);

/**
 * @brief Speak Ofelia, The Evil Witch of the WEST.
 * 
 * @param text What she says.
 * @param is_short If Ofelia's titles should be shortened.
 */
extern void speak_ofelia(char *text, int is_short);

/**
 * @brief Speak Gertrudis, The Evil Witch of the EAST.
 * 
 * @param text What she says.
 * @param is_short If Gertrudis' titles should be shortened.
 */
extern void speak_gertrudis(char *text, int is_short);

/**
 * @brief Speak Jasmine, The Good Witch of the SOUTH.
 * 
 * @param text What she says.
 * @param is_short If Jasmine's titles should be shortened.
 */
extern void speak_jasmine(char *text, int is_short);

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

