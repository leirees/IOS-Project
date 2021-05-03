/**
 * @file main_header.h
 * @author 2.2 Team developement group
 * @brief Header for general purposes, such as global variables and libraries used everywhere.
 * @version 0.1
 * @date 2021-05-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// System types, for C
#include <sys/types.h>
// Standard C library error codes
#include <errno.h>
// Characters.
#include "characters/character.h"

// Max line and args (length) definitions.
#define MAXLINE 200
#define MAXARGS 20

// Home directory
#define HOME "config/.gamedir"

/* KEYBOARD */
// Keyboard letters.
#define I_KEY 73
#define K_KEY 75

// Lowecase code ASCII gap.
#define LOWERCASE 22

// Arrow keys.
#define UP_ARROW 65
#define DOWN_ARROW 66
#define RIGHT_ARROW 67
#define LEFT_ARROW 68

#define ENTER_KEY 10

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

/* New DATATYPES */
//u8
typedef unsigned char u8;
//int8
typedef __INT8_TYPE__ int8;
//u16
typedef __U16_TYPE u16;
//int16
typedef short int16;
//u32
typedef unsigned int u32;

// Bool
typedef u8 bool;
#define true 1
#define false 0

/* GLOBAL VARIABLES */
static u8 state;

// Root dir
static char *root_dir;

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