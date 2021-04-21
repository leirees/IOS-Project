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

#define UP_ARROW    65
#define DOWN_ARROW  66
#define RIGHT_ARROW 67
#define LEFT_ARROW  68

// GLOBAL VARIABLES //
__INT8_TYPE__ STATE;

// Flags.
__INT8_TYPE__ exit_status;
// PID.
pid_t child_pid;
pid_t parent_pid;
// Fail counter.
__INT8_TYPE__ fails;

/**
 * STATUS OF THE GAME.
 */
#define CONFIG_TERM             -1
#define INIT_MENU               0
#define CHOOSE_MENU_OPTIONS     1
#define GAME_RUNNING            2
#define SHOW_SCORES             3
#define GAME_OVER_EXIT          4
#define GAME_OVER               5