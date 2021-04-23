/**
 * @file ansshell.c
 * @author IOS Lecturer, 2.2 Team
 * @brief Implementation of shell.
 * @version 0.1
 * @date 2021-03-10
 * 
 * @copyright Copyright (c) 2021
 */

// String library mod.
#include "libstring.h"

// CD call
#include "cd.h"

// Exit game call
#include "exit.h"

// Menu settings and functions
#include "menu.h"

// Signal handler
#include "signal_handler.h"

// MAIN
// Used for basic input/output stream
#include <stdio.h>
#include <stdlib.h>

// Used for handling directory files
#include <dirent.h>

// For EXIT codes and error handling
#include <errno.h>

// Unix syscall managing
#include <unistd.h>
#include <sys/wait.h>

#define error(a)            \
    {                       \
        printerr(a);        \
        exit(EXIT_FAILURE); \
    };
#define MAXLINE 200
#define MAXARGS 20

#define NUMCOMMANDS 13

#define HOME "config/.gamedir"

// ARROWS
#define UP_ARROW 65
#define DOWN_ARROW 66
#define RIGHT_ARROW 67
#define LEFT_ARROW 68

// PROMPT DESIGN
#define PROMPT_DESIGN concat(concat(ANSI_COLOR_BLUE, prompt_name), concat(ANSI_COLOR_RESET, "$ "))
#define PROMPT_NAME "GlindOS"

// GLOBAL VARIABLES //
static __INT8_TYPE__ STATE;

// Flags.
static __INT8_TYPE__ exit_status;
// PID.
static pid_t child_pid;
static pid_t parent_pid;
// Fail counter.
static __INT8_TYPE__ fails;

/**
 * KEYS
 */
#define ENTER_KEY 10

#define I_KEY 73
#define K_KEY 75

#define LOWERCASE 22

/**
 * STATUS OF THE GAME.
 */
#define CONFIG_TERM -1
#define INIT_MENU 0
#define CHOOSE_MENU_OPTIONS 1
#define GAME_RUNNING 2
#define SHOW_SCORES 3
#define GAME_OVER_EXIT 4
#define GAME_OVER 5

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