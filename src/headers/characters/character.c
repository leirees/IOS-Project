#include "character.h"

void create_player(player *p, char *name)
{
    p->name = name;
    p->fails = 0;
    p->score = 0;
    p->is_dead = 0;
}

void create_character(character *c, char *name, unsigned char has_magic, unsigned char is_evil, unsigned char is_with_you)
{
    // The name of the character.
    c->name = name;

    // Some flags to control the character.
    c->has_magic = has_magic;
    c->is_evil = is_evil;
    c->is_with_you = is_with_you;

    // When the character is created, is alive.
    c->is_dead = 0;
}

void speak_character(character *c, char *text)
{
    println((concat(c->name, ": "), text));
}

void create_charwtitle(character_with_title *c, char *name, char *short_title, char *long_title, unsigned char has_magic, unsigned char is_evil, unsigned char is_with_you)
{
    create_character(c->cwtitle, name, has_magic, is_evil, is_with_you);
    c->short_title = short_title;
    c->long_title = long_title;
}

void create_witch(character_with_title *c, char *name, char *short_title, char *long_title, unsigned char is_evil)
{
    create_charwtitle(c, name, short_title, long_title, 1, is_evil, 0);
}

void speak_charwtitle(character_with_title *someone, char *text, unsigned char is_title_short)
{
    println(concat(is_title_short ? someone->short_title : someone->long_title, text));
}