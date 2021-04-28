#include "headers/charplayer.h"

void create_player(player *p, char *name)
{
    p->name = name;

    p->fails = 0;
    p->score = 0;

    p->is_dead = 0;
}