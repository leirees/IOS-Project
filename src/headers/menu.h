/**
 * @file menu.h
 * @author David Cuenca, Team 2.2
 * @brief Menu header file.
 * @version 0.1
 * @date 2021-05-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "main_header.h"
// Terminal state save.
#include <termios.h>

/**
 * @brief Restores the terminal, from a previous state.
 * @param saved_glindos The terminal settings to restore;
 */
void restore_terminal(struct termios *saved_glindos);

/**
 * @brief Clean the screen of the terminal.
 * 
 */
void clear_screen();

/**
* @brief The menu screen!
*/
void print_menu();

/**
 * @brief The options menu!
 * @param selected_option The selected option, as an integer.
 */
void print_menu_options(u8 selected_option);
