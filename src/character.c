#include "headers/character.h"

void create_character(character *c, char *name, unsigned char has_magic, unsigned char is_evil, unsigned char is_neutral, unsigned char is_with_you)
{
    // The name of the character.
    c->name = name;

    // Some flags to control the character.
    c->has_magic = has_magic;
    c->is_evil = is_evil;
    c->is_neutral = is_neutral;
    c->is_with_you = is_with_you;

    // When the character is created, is alive.
    c->is_dead = 0;
}

void speak_character(character *c, char *text)
{
    println((concat(c->name, ": "), text));
}