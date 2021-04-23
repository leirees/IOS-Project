#include "character.h"

#define TREES       underlined(bold("Forest trees"))
#define GUARDIAN    undelined(bold("Guardian"))
#define GHOST       underlined(bold("Ghost"))
#define ADMIN       underlined(bold("ADMIN"))

static character trees;
static character guardian;
static character ghost;
static character admin;

/**
 * @brief Create a trees object.
 * 
 */
extern void create_trees();

/**
 * @brief Create a guardian object.
 * 
 */
extern void create_guardian();

/**
 * @brief Create a ghost object.
 * 
 */
extern void create_ghost();

/**
 * @brief Create a ADMIN object.
 * 
 */
extern void create_admin();