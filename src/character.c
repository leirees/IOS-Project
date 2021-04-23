#include "headers/character.h"

void speak(character *c, char *text)
{
    println((concat(c->name, ": "), text));
}