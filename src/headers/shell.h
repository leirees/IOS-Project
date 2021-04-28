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

// Number of commands.
#define NUMCOMMANDS 13

// PROMPT DESIGN
#define PROMPT_DESIGN concat(concat(ANSI_COLOR_BLUE, prompt_name), concat(ANSI_COLOR_RESET, "$ "))
#define PROMPT_NAME "GlindOS"

// CD call
#include "cd.h"

// Exit game call
#include "exit.h"

// Menu settings and functions
#include "menu.h"

// Signal handler
#include "signal_handler.h"

/**
 * @brief Process signals SIGINT and SIGTSTP, with particular behaviors.
 */
void setup_signals();

/**
 * @brief Setup all the characters, variables.
 * 
 */
void setup();

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
int read_args(int *argcp, char *args[], int max, int *eofp);

/**
 * @brief Execute a process, given a command and its arguments.
 * 
 * @param argc Argument counter: the number of arguments that are passed (int, >= 1).
 * @param argv Argument vector: the arguments that are passed (char*, len(char*) >= 1)
 * @return int -1 if error creating the process, 1 if error while executing the process or 0 if ok.
 */
int execute(int argc, char *argv[]);