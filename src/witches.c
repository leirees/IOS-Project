#include "headers/witches.h"

void create_glinda()
{
    glinda.is_evil      = 0;
    glinda.real_title   = GLINDA;
    glinda.short_title  = SHORT_GLINDA;
}

void create_ofelia()
{
    ofelia.is_evil      = 1;
    ofelia.real_title   = OFELIA;
    ofelia.short_title  = SHORT_OFELIA;
}

void create_gertrudis()
{
    gertrudis.is_evil       = 1;
    gertrudis.real_title    = GERTRUDIS;
    gertrudis.short_title   = SHORT_GERTRUDIS;
}

void create_jasmine() 
{
    jasmine.is_evil     = 0;
    jasmine.real_title  = JASMINE;
    jasmine.short_title = SHORT_JASMINE;
}


void speak_glinda(char *text, int is_short)
{
    speak(&glinda, text, is_short);
}

void speak_ofelia(char *text, int is_short)
{
    speak(&ofelia, text, is_short);
}

void speak_gertrudis(char *text, int is_short)
{
    speak(&gertrudis, text, is_short);
}

void speak_jasmine(char *text, int is_short)
{
    speak(&jasmine, text, is_short);
}
