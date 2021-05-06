#include "character.h"

#include "../libstring/libstring.h"
#include <stdlib.h>

void create_player(player *p, char *name)
{
    p->name = (char*)malloc(strlen(name));
    p->name = name;

    p->fails = 0;
    p->score = 0;
    p->is_dead = 0;
    println("Creating PLAYER... OK");
}

void create_character(character *c, char *name, unsigned char has_magic, unsigned char is_evil, unsigned char is_with_you)
{
    // The name of the character.
    c->name = (char*)malloc(strlen(name));
    c->name = name;

    // Some flags to control the character.
    c->has_magic = has_magic;
    c->is_evil = is_evil;
    c->is_with_you = is_with_you;

    // When the character is created, is alive.
    c->is_dead = 0;
    println(concat(concat("Creating character ", name), "...OK"));
}

void create_charwtitle(character_with_title *c, char *name, char *short_title, char *long_title, unsigned char has_magic, unsigned char is_evil, unsigned char is_with_you)
{
    c->name = (char*)malloc(strlen(name));
    c->name = name;
    
    c->short_title = short_title;
    c->long_title = long_title;
    c->has_magic = has_magic;
    c->is_evil = is_evil;

    // Is the character with you?
    c->is_with_you = is_with_you;

    // Is the character dead?
    c->is_dead = 0;
    println(concat(concat("Creating character ", name), "...OK"));
}

void create_witch(character_with_title *c, char *name, char *short_title, char *long_title, unsigned char is_evil)
{
    create_charwtitle(c, name, short_title, long_title, 1, is_evil, 0);
}

void speak_character(char *title, char *text)
{
    println((concat(concat(title, ": "), text)));
}