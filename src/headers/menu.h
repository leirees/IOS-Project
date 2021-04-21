#include <termios.h>
#include "libstring.h"

/**
 * @brief Restores the terminal, from a previous state.
 * @param saved_glindos The terminal settings to restore;
 */
void restore_terminal(struct termios saved_glindos);

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
void print_menu_options(__INT8_TYPE__ selected_option);

