/**
 * @file ansshell.c
 * @author IOS Lecturer, 2.2 Team
 * @brief Implementation of shell.
 * @version 0.1
 * @date 2021-03-10
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/shell.h"

char *args[MAXARGS];
int8 status;
int16 argc;
bool eof;

u8 last_state;

void setup_signals()
{
   signal(SIGINT, signal_handler);
   signal(SIGTSTP, signal_handler);
}

void setup_game()
{
   // Root dir
   root_dir = getcwd((char *)NULL, 0);

   // PID
   child_pid = -1;
   parent_pid = getpid();

   create_characters();
}

void create_characters()
{
   /* Characters creation */
   // Companion creation
   char *scarecrown_name = SCARECROWN;
   char *tinman_name = TINMAN;
   char *lion_name = LION;

   create_character(&scarecrown, scarecrown_name, false, false, true);
   create_character(&lion, lion_name, false, false, true);
   create_character(&tinman, tinman_name, false, false, true);

   // Witches creation
   char *short_title_glinda = SHORT_GLINDA;
   char *short_title_ofelia = SHORT_OFELIA;
   char *short_title_gertrudis = SHORT_GERTRUDIS;
   char *short_title_jasmine = SHORT_JASMINE;
   char *title_glinda = GLINDA;
   char *title_ofelia = OFELIA;
   char *title_gertrudis = GERTRUDIS;
   char *title_jasmine = JASMINE;

   create_witch(&glinda, "Glinda", short_title_glinda, title_glinda, false);
   create_witch(&ofelia, "Ofelia", short_title_ofelia, title_ofelia, true);
   create_witch(&gertrudis, "Gertrudis", short_title_gertrudis, title_gertrudis, true);
   create_witch(&jasmine, "Jasmine", short_title_jasmine, title_jasmine, false);

   // Secondary characters
   char *admin_name = ADMIN;
   create_character(&admin, admin_name, true, false, false);

   char *dog_name = DOG;
   create_character(&dog, dog_name, false, false, false);

   // Extras
   char *trees_name = TREES;
   char *ghost_name = GHOST;
   char *guardian_name = GUARDIAN;

   create_character(&trees, trees_name, false, false, false);
   create_character(&ghost, ghost_name, true, false, false);
   create_character(&guardian, guardian_name, false, false, false);
}

int read_args(int *argcp, char *args[], int max, int *eofp)
{
   static char cmd[MAXLINE];
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
      execvp(argv[0], argv);
      break;

   default:
      // Parent process.
      wait(NULL);
      break;
   }

   return EXIT_SUCCESS;
}

int shell(char *path[NUMCOMMANDS], char *err_title, char *prompt)
{
   u8 command;

   // Print the prompt on screen.
   print(prompt);

   if (read_args(&argc, args, MAXARGS, &eof) && argc > 0)
   {
      // Check commands from path.
      for (command = 0; command < NUMCOMMANDS; command++)
      {
         if (!strcmp(args[0], path[command]))
         {
            if (!strcmp(args[0], "cd"))
            {
               // CD command.
               cd(args[1]);
            }
            else if (!strcmp(args[0], "exit"))
            {
               // EXIT command.
               last_state = state;
               state = GAME_OVER_EXIT;
            }
            else
            {
               args[0] = concat(concat(root_dir, "/bin/"), path[command]);
               status = execute(argc, args);
            }
            break;
         }
      }

      // Check commands from outside the path (executable files).
      if (!strncmp("./", args[0], 2))
      {
         status = execute(argc, args);
      }
   }

   if (eof)
   {
      return EXIT_SUCCESS;
   }
}

int main()
{
   // Setup System Agent: the one that provides its body as the work in which we work.
   char *err_title = THE_SYSTEM;

   // Setup command path.
   char *path[NUMCOMMANDS] = COMMANDS;

   // Set the default prompt design.
   char *prompt = PROMPT;

   // Setup signals
   setup_signals();

   // 1. Set game state to configuration state, and deal with signal handling.
   state = CONFIG_TERM;

   do
   {
      switch (state)
      {
      case CONFIG_TERM:
         // Setup game and change state.
         setup_game();
         last_state = state;
         state = INIT_MENU;
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
         u8 option = 0;
         do
         {
            print_menu_options(option);
            scanf("%d", &option);
            print_menu_options(option);
         } while (getchar() != ENTER_KEY);

         last_state = state;

         // Enter the game :)
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
         break;

      case GAME_RUNNING:
         shell(path, err_title, prompt);
         break;

      case GAME_OVER_EXIT:
         if (exit_game())
         {
            state = CONFIG_TERM;
         }
         else
         {
            state = last_state;
         }
         break;
      }
   } while (true);

   _exit(EXIT_SUCCESS);
}
