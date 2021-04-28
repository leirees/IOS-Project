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