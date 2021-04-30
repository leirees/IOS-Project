/**
 * @file charplayer.h
 * @author Team 2.2 The Wizard of OS
 * @brief Player character.
 * @version 0.1
 * @date 2021-04-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "libstring.h"

typedef struct
{
    char *name;
    unsigned char is_dead;
    unsigned char fails;
    unsigned int score;
} player;

/**
 * @brief Create a player object.
 * 
 * @param p The player.
 * @param name The name of the player.
 */
extern void create_player(player *p, char *name);