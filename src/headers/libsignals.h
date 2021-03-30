/**
 * @file signal_handler.h
 * @author David Cuenca Marcos
 * @brief Deal with signals, easily.
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

// Unix signal handler
#include <signal.h>

/**
 * @brief Function to deal with SIGTERM.
 */
void signal_term(int foo);