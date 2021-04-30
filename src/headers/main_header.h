/**
 * @file main_header.h
 * @author 2.2 Team developement group
 * @brief Header for general purposes, such as global variables and libraries used everywhere.
 * @version 0.1
 * @date 2021-04-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Remove cyclical imports TODO:

// Modified String Library, by 2.2 Team.
#include "libstring.h"

// Basic IO stream
#include <stdio.h>
#include <stdlib.h>

// Hadle directory files
#include <dirent.h>

// Exit codes and error handling
#include <errno.h>

// Unix syscalls
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

// Character struct.
// #include "character.h"
#include "charwtitle.h"
#include "charcomp.h"
#include "charwitch.h"
#include "charextra.h"
#include "charplayer.h"

// Home directory
#define HOME "config/.gamedir"

// Define new datatypes
typedef unsigned char u8;
typedef __INT8_TYPE__ int8;
typedef __U16_TYPE u16;
typedef short int16;
typedef unsigned int u32;
typedef char *string;

#define error(a)            \
    {                       \
        printerr(a);        \
        exit(EXIT_FAILURE); \
    };

#define MAXLINE 200
#define MAXARGS 20

/**
 * Keyboard keys.
 */
#define UP_ARROW 65
#define DOWN_ARROW 66
#define RIGHT_ARROW 67
#define LEFT_ARROW 68

#define ENTER_KEY 10

#define I_KEY 73
#define K_KEY 75

// Lowecase code ASCII (use the sum)
#define LOWERCASE 22

// Boolean values
#define true 1
#define false 0

/**
 * New status of the game.
 */
#define CONFIG_TERM -1
#define INIT_MENU 0
#define CHOOSE_MENU_OPTIONS 1
#define GAME_RUNNING 2
#define SHOW_SCORES 3
#define GAME_OVER_EXIT 4
#define GAME_OVER 5

// GLOBAL VARIABLES //
static u8 state;
static u8 exit_status;

// PID.
static pid_t child_pid;
static pid_t parent_pid;

// Character's definition.
// Main character
static player dorothy;

static character scarecrown;
static character tinman;
static character lion;

static character_with_title glinda;
static character_with_title ofelia;

// Secondary character
static character admin;
static character dog;

static character_with_title gertrudis;
static character_with_title jasmine;

// Extras
static character trees;
static character guardian;
static character ghost;