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
#define GAME_OVER_EXIT 4
#define GAME_OVER 5

/* GLOBAL VARIABLES */
static int state;
static int last_state;

// Root dir
static char *root_dir;

// PID.
static pid_t parent_pid;
static pid_t child_pid;

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
   char cmd[MAXLINE];
   char *cmdp;
   int ret, i = 0;

   *argcp = 0;
   *eofp = 0;

   do
   {
      ret = read(0, cmd + i, 1);
      if (cmd[i] == '\n')
      {
         // Correct line
         break;
      }
      i++;

      if (i >= MAXLINE)
      {
         // Line too long
         ret = -2;
         break;
      }
   } while (ret == 1);

   switch (ret)
   {
   case 1:
      // Correct reading
      cmd[i + 1] = '\0';
      break;

   case 0:
      // End of file
      *eofp = 1;
      return EXIT_SUCCESS;

   case -1:
      // Reading failure
      *argcp = -1;
      fprintf(stderr, "Reading failure \n");
      return EXIT_SUCCESS;

   case -2:
      // Line too long
      *argcp = -1;
      fprintf(stderr, "Line too long -- removed command\n");
      return EXIT_SUCCESS;
   }

   // Analyzing the line
   cmdp = cmd;
   for (i = 0; i < max; i++)
   {
      args[i] = strtok(cmdp, " \t\n");
      /* to show every argument */
      if (args[i] == (char *)NULL)
         break;

      cmdp = NULL;
   }

   if (i >= max)
   {
      fprintf(stderr, "Too many arguments -- removed command\n");
      return 0;
   }

   *argcp = i;
   return EXIT_FAILURE;
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
   child_pid = fork();

   switch (child_pid)
   {
   case -1:
      // Error in fork() (not so common)
      return EXIT_FAILURE;

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

   return EXIT_SUCCESS;
}

int main()
{
   char *err_title = THE_SYSTEM;
   char *game_dir = "$HOME";
   char *prompt;

   // Change the official dir to the root dir.
   // chdir((const char *)root);
   char *args[MAXARGS];
   int argc;
   int eof;

   DIR *path;
   struct dirent *cmd;

   short command;

   int status;
   short option;

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
         // Setup game and change state.
         println("Setting the game up...");

         // Root dir
         root_dir = getcwd((char *)NULL, 0);

         // PID
         parent_pid = getpid();
         child_pid = -1;

         /* Characters creation */
         // Companion creation
         char *scarecrown_name = SCARECROWN;
         char *tinman_name = TINMAN;
         char *lion_name = LION;

         create_character(&scarecrown, scarecrown_name, 0, 0, 1);
         create_character(&lion, lion_name, 0, 0, 1);
         create_character(&tinman, tinman_name, 0, 0, 1);

         // Witches creation
         char *short_title_glinda = SHORT_GLINDA;
         char *short_title_ofelia = SHORT_OFELIA;
         char *short_title_gertrudis = SHORT_GERTRUDIS;
         char *short_title_jasmine = SHORT_JASMINE;
         char *title_glinda = GLINDA;
         char *title_ofelia = OFELIA;
         char *title_gertrudis = GERTRUDIS;
         char *title_jasmine = JASMINE;

         create_witch(&glinda, "Glinda", short_title_glinda, title_glinda, 0);
         create_witch(&ofelia, "Ofelia", short_title_ofelia, title_ofelia, 1);
         create_witch(&gertrudis, "Gertrudis", short_title_gertrudis, title_gertrudis, 1);
         create_witch(&jasmine, "Jasmine", short_title_jasmine, title_jasmine, 0);

         // Secondary characters
         char *admin_name = ADMIN;
         create_character(&admin, admin_name, 1, 0, 0);

         char *dog_name = DOG;
         create_character(&dog, dog_name, 0, 0, 0);

         // Extras
         char *trees_name = TREES;
         char *ghost_name = GHOST;
         char *guardian_name = GUARDIAN;

         create_character(&trees, trees_name, 0, 0, 0);
         create_character(&ghost, ghost_name, 1, 0, 0);
         create_character(&guardian, guardian_name, 0, 0, 0);

         last_state = state;
         println("OK\n");

         state = INIT_MENU;

         println("Initialising game menu. OK");
         println("Press enter to continue...");

         scanf("%c", NULL);

         break;

      case INIT_MENU:
         // Initial menu: if ENTER_KEY pressed, go to CHOOSE_MENU_OPTIONS.
         do
         {
            print_menu();
         } while (getchar() != ENTER_KEY);

         last_state = state;
         state = CHOOSE_MENU_OPTIONS;
         break;

      case CHOOSE_MENU_OPTIONS:
         // Choose menu options.
         option = 0;
         print_menu_options(option);
         scanf("%d", &option);

         if (option)
         {
            print_menu_options(option);

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
               state = GAME_OVER_EXIT;
               break;
            }
         }

         clear_screen();

         break;

      case GAME_RUNNING:
         prompt = concat(concat(ANSI_COLOR_BLUE, concat(PROMPT_NAME, ANSI_COLOR_RESET)), concat(concat("[", concat(game_dir, "]")), "$"));

         while (1)
         {
            // Print the prompt on screen.
            print(prompt);

            if (read_args(&argc, args, MAXARGS, &eof) && argc > 0)
            {
               path = opendir(concat(root_dir, "/bin"));

               if (!path)
               {
                  if (errno == ENOENT)
                  {
                     printerr("Oh, oh... NO root dir!", err_title);
                  }
                  else
                  {
                     printerr("Oh, oh... cannot open root dir!", err_title);
                  }
               }

               while ((cmd = readdir(path)) != NULL)
               {
                  if (!strncmp(cmd->d_name, args[0], 20))
                  {
                     args[0] = concat("/bin/", args[0]);
                     status = execute(argc, args);
                     break;
                  }
               }

               closedir(path);

               if (!strcmp(args[0], "cd"))
               {
                  if (argc == 2)
                  {
                     // CD command, to some place.
                     if (cd(args[1]) != -1)
                     {
                        if (!strcmp(args[1], "~") || !strcmp(args[1], "$HOME") || !strcmp(args[1], "village"))
                        {
                           game_dir = "$HOME";
                        }
                        else
                        {
                           game_dir = concat(game_dir, args[1]);
                        }
                     }
                     else
                     {
                        printerr("Not POSSIBLE TO MOVE", err_title);
                     }
                  }
                  else if (argc == 1)
                  {
                     // Else, go to the game root dir.
                     cd(root_dir);
                     game_dir = "$HOME";
                  }
                  else
                  {
                     printerr("Oh, oh... CD not OK!", err_title);
                  }
               }
               else if (!strcmp(args[0], "exit"))
               {
                  // EXIT command.
                  last_state = state;
                  state = GAME_OVER_EXIT;
               }

               // Check commands from outside the path.
               if (!strncmp("./", args[0], 2))
               {
                  status = execute(argc, args);
               }
            }

            if (eof)
            {
               return EXIT_FAILURE;
            }
               }
         break;

      case GAME_OVER_EXIT:
         if (exit_game())
         {
            state = last_state;
         }
         else
         {
            if (last_state == GAME_RUNNING)
            {
               state = CONFIG_TERM;
            }
            else if (last_state == CHOOSE_MENU_OPTIONS)
            {
               _exit(EXIT_SUCCESS);
            }
         }
         break;
      }
   } while (1);

   return 0;
}
