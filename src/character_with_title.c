#include "headers/character_with_title.h"

void speak(character_with_title *someone, char *text, unsigned char is_title_short)
{
    char *title;

    if (is_title_short)
    {
        title = someone->short_title;
    }
    else
    {
        title = someone->real_title;
    }

    println(concat(title, text));
}