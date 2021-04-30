/**
 * @file charplayer.c
 * @author Team 2.2 The Wizard of OS
 * @brief Player character.
 * @version 0.1
 * @date 2021-04-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "headers/charplayer.h"

void create_player(player *p, char *name)
{
    p->name = name;
    p->fails = 0;
    p->score = 0;
    p->is_dead = 0;
}