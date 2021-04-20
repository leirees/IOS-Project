/**
 * @file ansshell.c
 * @author IOS Lecturer, 2.2 Team
 * @brief Implementation of shell.
 * @version 0.1
 * @date 2021-03-10
 * 
 * @copyright Copyright (c) 2021
 */

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

// Signals and signal handlers
#include <signal.h>

// String library mod.
#include "libstring.h"

// CD call
#include "cd.h"

// Exit game call
#include "exit.h"

// TERMIOS
#include <termios.h>

#define error(a)            \
    {                       \
        printerr(a);        \
        exit(EXIT_FAILURE); \
    };
#define MAXLINE 200
#define MAXARGS 20

#define NUMCOMMANDS 13

#define HOME "config/.gamedir"

#define UP_ARROW    65
#define DOWN_ARROW  66
#define RIGHT_ARROW 67
#define LEFT_ARROW  68

/**
 * @brief Signal handler, in case of signals like Ctrl-C or Ctrl-Z,
 * to get custom behaviors.
 * 
 * @param sig Signal code.
 */
void signal_handler(int sig);

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