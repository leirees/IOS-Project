/**
 * @file ansshell.c
 * @author IOS Lecturer, 2.2 Team
 * @brief Implementation of shell.
 * @version 0.1
 * @date 2021-03-10
 * 
 * @copyright Copyright (c) 2021
 */

// CD command.
#include "headers/cd.h"
// Exit command.
#include "headers/exit.h"
// Menus.
#include "headers/menu.h"
// Signal handler.
#include "headers/signal_handler.h"
// Characters list.
#include "headers/characters/character.h"
// Mod. libstring.h
#include "headers/libstring/libstring.h"
#include "headers/clear.h"

#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Number of commands in the main path.
#define NUMCOMMANDS 13
// Prompt name.
#define PROMPT_NAME "GlindOS"

#define MAXLINE 200
#define MAXARGS 20

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
#define EXIT 4
#define GAME_OVER 5

/* GLOBAL VARIABLES */
int state;
int last_state;

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
int read_args(int *argcp, char *args[], int max, int *eofp)
{
   static char cmd[MAXLINE];
   char *cmdp;
   int ret, i;

   *argcp = 0;
   *eofp = 0;
   i = 0;
   while ((ret = read(0, cmd + i, 1)) == 1)
   {
      if (cmd[i] == '\n')
         break; // correct line
      i++;
      if (i >= MAXLINE)
      {
         ret = -2; // line too long
         break;
      }
   }
   switch (ret)
   {
   case 1:
      cmd[i + 1] = '\0'; // correct reading
      break;
   case 0:
      *eofp = 1; // end of file
      return 0;
      break;
   case -1:
      *argcp = -1; // reading failure
      fprintf(stderr, "Reading failure \n");
      return 0;
      break;
   case -2:
      *argcp = -1; // line too long
      fprintf(stderr, "Line too long -- removed command\n");
      return 0;
      break;
   }
   // Analyzing the line
   cmdp = cmd;
   for (i = 0; i < max; i++)
   { /* to show every argument */
      if ((args[i] = strtok(cmdp, " \t\n")) == (char *)NULL)
         break;
      cmdp = NULL;
   }
   if (i >= max)
   {
      fprintf(stderr, "Too many arguments -- removed command\n");
      return 0;
   }
   *argcp = i;
   return 1;
}

/**
 * @brief Execute a process, given a command and its arguments.
 * 
 * @param argc Argument counter: the number of arguments that are passed (int, >= 1).
 * @param argv Argument vector: the arguments that are passed (char*, len(char*) >= 1)
 * @return int -1 if error creating the process, 1 if error while executing the process or 0 if ok.
 */
int execute(int argc, char *argv[])
{
   pid_t child_pid = fork();

   switch (child_pid)
   {
   case -1:
      return 1;
      break;

   case 0:
      // Child process
      signal(SIGINT, signint_child);
      execvp(argv[0], argv);
      break;

   default:
      // Parent process.
      wait(NULL);
      signal(SIGINT, signint_parent);
      break;
   }

   return 0;
}

int main()
{

   const char *err_title = THE_SYSTEM;
   const char *root_dir = getcwd((char *)NULL, 0);
   const char *game_dir = concat(root_dir, "/config/.gamedir");

   char *args[MAXARGS];
   int argc;
   int eof;

   short command;
   short option;
   int buffstatus;

   // Setup signals
   print("Setting up signals...");
   signal(SIGINT, signint_parent);
   signal(SIGTSTP, signstp);
   print("OK\n");

   // 1. Set game state to configuration state, and deal with signal handling.
   state = CONFIG_TERM;

   do
   {
      switch (state)
      {
      case CONFIG_TERM:
         println("Setting the game up...");

         // Set in root dir
         chdir(root_dir);

         /* Characters creation */
         // Companion creation
         char *scarecrown_name = SCARECROWN;
         char *tinman_name = TINMAN;
         char *lion_name = LION;

         // Witches creation
         char *short_title_glinda = SHORT_GLINDA;
         char *short_title_ofelia = SHORT_OFELIA;
         char *short_title_gertrudis = SHORT_GERTRUDIS;
         char *short_title_jasmine = SHORT_JASMINE;
         char *title_glinda = GLINDA;
         char *title_ofelia = OFELIA;
         char *title_gertrudis = GERTRUDIS;
         char *title_jasmine = JASMINE;

         char *admin_name = ADMIN;

         char *dog_name = DOG;

         char *trees_name = TREES;
         char *ghost_name = GHOST;
         char *guardian_name = GUARDIAN;

         create_character(&scarecrown, scarecrown_name, 0, 0, 1);
         create_character(&lion, lion_name, 0, 0, 1);
         create_character(&tinman, tinman_name, 0, 0, 1);

         create_witch(&glinda, "Glinda", short_title_glinda, title_glinda, 0);
         create_witch(&ofelia, "Ofelia", short_title_ofelia, title_ofelia, 1);
         create_witch(&gertrudis, "Gertrudis", short_title_gertrudis, title_gertrudis, 1);
         create_witch(&jasmine, "Jasmine", short_title_jasmine, title_jasmine, 0);

         // Secondary characters
         create_character(&admin, admin_name, 1, 0, 0);
         create_character(&dog, dog_name, 0, 0, 0);

         // Extras
         create_character(&trees, trees_name, 0, 0, 0);
         create_character(&ghost, ghost_name, 1, 0, 0);
         create_character(&guardian, guardian_name, 0, 0, 0);

         println("OK\n");

         println("Initialising game menu. OK");
         println("Press enter to continue...");

         do
         {

         } while (getchar() != ENTER_KEY);

         last_state = state;
         state = INIT_MENU;

         break;

      case INIT_MENU:
         clear_screen();

         do
         {
            print_menu();
         } while (getchar() != ENTER_KEY);

         last_state = state;
         state = CHOOSE_MENU_OPTIONS;

         break;

      case CHOOSE_MENU_OPTIONS:
         clear_screen();

         print_menu_options();
         scanf("%d", &option);

         last_state = state;

         switch (option)
         {
         case 1:
            state = GAME_RUNNING;
            break;

         case 2:
            state = SHOW_SCORES;
            break;

         case 3:
            state = EXIT;
            break;
         }

         clear_screen();

         break;

      case GAME_RUNNING:
         print(concat(concat(ANSI_COLOR_BLUE, concat(PROMPT_NAME, ANSI_COLOR_RESET)), concat(concat("[", concat(game_dir, "]")), "$ ")));

         if (read_args(&argc, args, MAXARGS, &eof) && argc > 0)
         {
            if (!strcmp(args[0], "exit"))
            {
               state = EXIT;
               continue;
            }

            if (!strncmp(args[1], "./", 2))
            {
               buffstatus = execute(argc, args);
            }
         }

         if (eof)
         {
            return 1;
         }

         break;

      case EXIT:
         exit_game();
         break;
      }

   } while (1);

   return 0;
}
