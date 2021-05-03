/**
 * @file ansshell.c
 * @author IOS Lecturer, 2.2 Team
 * @brief Implementation of shell.
 * @version 0.1
 * @date 2021-03-10
 * 
 * @copyright Copyright (c) 2021
 */

#include "main_header.h"
// Signal handler
#include "signal_handler.h"
#include <sys/wait.h>

/* COMMANDS for the game */
#define NUMCOMMANDS 13
#define COMMANDS                                                                                     \
    {                                                                                                \
        "cat", "cd", "cp", "exit", "grep", "help", "ls", "mv", "pwd", "stee", "touch", "help", "man" \
    }

// CD
#include "cd.h"
// EXIT
#include "exit.h"

/* Menu settings and functions */
#include "menu.h"

// PROMPT DESIGN
#define PROMPT_NAME "GlindOS"
#define PROMPT concat(concat(ANSI_COLOR_BLUE, PROMPT_NAME), concat(ANSI_COLOR_RESET, "$ "))

/**
 * @brief Setup all the characters, variables.
 * 
 */
void setup_game();

/**
 * @brief Process signals SIGINT and SIGTSTP, with particular behaviors.
 */
void setup_signals();

/**
 * @brief Creates all character objects for the game.
 * 
 */
void create_characters();

/**
 * @brief Read all the entries in a line of written code, for shell.
 * For reading commands.
 * 
 * @param argcp 
 * @param args 
 * @param max 
 * @param eofp 
 * @return int 
 */
int read_args(int16 *argcp, char *args[], int max, bool *eofp);

/**
 * @brief Execute a process, given a command and its arguments.
 * 
 * @param argc Argument counter: the number of arguments that are passed (int, >= 1).
 * @param argv Argument vector: the arguments that are passed (char*, len(char*) >= 1)
 * @return int -1 if error creating the process, 1 if error while executing the process or 0 if ok.
 */
int execute(int argc, char *argv[]);

/**
 * @brief Shell object, for game.
 * 
 * @param path The path with all the commands.
 * @param err_title The error title, for error handling.
 * @param prompt The prompt design.
 * @return int 1 iff failure.
 */
int shell(char *path[NUMCOMMANDS], char *err_title, char *prompt);