/**
 * @file exit.h
 * @author David Cuenca
 * @brief Exit, for shell.
 * @version 0.1
 * @date 2021-03-17
 * 
 * @copyright Copyright (c) 2021
 */

#include "main_header.h"

// Basic IO stream
#include <stdio.h>
#include <stdlib.h>
// Modified String Library, by 2.2 Team.
#include "libstring.h"
// Include witches
#include "charwitch.h"

/**
 * @brief Finish the execution of the terminal.
 * Indeed, exit the game at once.
 * 
 * @return int 0 if successfully exited.
 */
extern int exit_game();