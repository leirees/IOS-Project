#include "headers/charwtitle.h"

void create_charwtitle(character_with_title *c, char *name, char *short_title, char *long_title, unsigned char has_magic, unsigned char is_evil, unsigned char is_neutral, unsigned char is_with_you)
{
    create_character(c->cwtitle, name, has_magic, is_evil, is_neutral, is_with_you);
    c->short_title = short_title;
    c->long_title = long_title;
}

void speak_charwtitle(character_with_title *someone, char *text, unsigned char is_title_short)
{
    char *title;

    if (is_title_short)
    {
        title = someone->short_title;
    }
    else
    {
        title = someone->long_title;
    }

    println(concat(title, text));
    free(title);
}