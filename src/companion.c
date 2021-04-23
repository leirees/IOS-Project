#include "headers/companion.h"

void create_scarecrown()
{
    scarecrown.name = SCARECROWN;
    scarecrown.is_with_you = 1;
}

void create_tinman(__INT8_TYPE__ is_with_you)
{
    tinman.name = TINMAN;
    tinman.is_with_you = is_with_you;
}

void create_lion()
{
    lion.name = LION;
    lion.is_with_you = 1;
}

void create_dog()
{
    dog.name = DOG;
    dog.is_with_you = 1;
}

void kill_dog()
{
    dog.is_with_you = 0;
}

void speak_scarecrown(char *text)
{
    speak(&scarecrown, text);
}

void speak_tinman(char *text)
{
    speak(&tinman, text);
}

void speak_lion(char *text)
{
    speak(&lion, text);
}

void speak_toto(char *text)
{
    speak(&dog, text);
}