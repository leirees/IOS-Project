/**
 * @file charwtitle.c
 * @author Team 2.2 The Wizard of OS
 * @brief Character with title object.
 * @version 0.1
 * @date 2021-04-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "headers/charwtitle.h"

void create_charwtitle(character_with_title *c, char *name, char *short_title, char *long_title, unsigned char has_magic, unsigned char is_evil, unsigned char is_neutral, unsigned char is_with_you)
{
    create_character(c->cwtitle, name, has_magic, is_evil, is_neutral, is_with_you); // TODO: evil = 0; good = 1; neutral = -1;
    c->short_title = short_title;
    c->long_title = long_title;
}

void create_witch(character_with_title *c, char *name, char *short_title, char *long_title, unsigned char is_evil) {
    create_charwtitle(c, name, short_title, long_title, 1, is_evil, 0, 0);
}

void speak_charwtitle(character_with_title *someone, char *text, unsigned char is_title_short)
{
    println(concat(is_title_short ? someone->short_title : someone->long_title, text));
}