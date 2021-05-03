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
u8 eof = 0;

u8 from_path;
u8 command;
u8 chosen_option;

void setup_signals()
{
   signal(SIGINT, signal_handler);
   signal(SIGTSTP, signal_handler);
}

void setup_game()
{
   // PID
   child_pid = -1;
   parent_pid = getpid();

   // FLAGS
   exit_status = 1;

   create_characters();
}

void create_characters()
{
   /* Characters creation */
   // Companion creation
   char *scarecrown_name = SCARECROWN;
   char *tinman_name = TINMAN;
   char *lion_name = LION;

   create_character(&scarecrown, scarecrown_name, false, false, false, true);
   create_character(&tinman, tinman_name, false, false, false, true);
   create_character(&lion, lion_name, false, false, false, true);

   // Witches creation
   char *short_title_glinda = SHORT_GLINDA;
   char *short_title_ofelia = SHORT_OFELIA;
   char *title_glinda = GLINDA;
   char *title_ofelia = OFELIA;

   create_charwtitle(&glinda, "Glinda", short_title_glinda, title_glinda, true, false, false, false);
   create_charwtitle(&ofelia, "Ofelia", short_title_ofelia, title_ofelia, true, true, false, false);

   // Secondary characters
   char *admin_name = ADMIN;
   create_character(&admin, admin_name, true, false, false, false);

   char *dog_name = DOG;
   create_character(&dog, dog_name, false, false, false, false);

   char *short_title_gertrudis = SHORT_GERTRUDIS;
   char *short_title_jasmine = SHORT_JASMINE;
   char *title_gertrudis = GERTRUDIS;
   char *title_jasmine = JASMINE;

   // TODO: witch constructor.
   create_charwtitle(&gertrudis, "Gertrudis", short_title_gertrudis, title_gertrudis, true, true, false, false);
   create_charwtitle(&jasmine, "Jasmine", short_title_jasmine, title_jasmine, true, false, false, false);

   // TODO: extras constructor.
   // Extras
   char *trees_name = TREES;
   char *ghost_name = GHOST;
   char *guardian_name = GUARDIAN;

   create_character(&trees, trees_name, false, false, true, false);
   create_character(&ghost, ghost_name, false, false, true, false);
   create_character(&guardian, guardian_name, false, false, true, false);
}

int read_args(int *argcp, char *args[], int max, int *eofp)
{
   static char cmd[MAXLINE];
   char *cmdp;
   int ret, i;

   i = 0;
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
      // Error on creating the child process.
      return EXIT_FAILURE;

   case 0:
      // Child process' program.
      // Execute the give command, if possible.
      execvp(argv[0], argv);
      break;

   default:
      // Parent process execution.
      wait(NULL);
      break;
   }

   return EXIT_SUCCESS;
}

void shell()
{
   // Declare local variables.
   char *path[NUMCOMMANDS] = {"cat", "cd", "cp", "exit", "grep", "help", "ls", "mv", "pwd", "stee", "touch", "help", "man"};
   char *root_dir = getcwd((char *)NULL, 0); 

   // Set the default prompt design.
   char *prompt_name = PROMPT_NAME;
   char *prompt = PROMPT_DESIGN;

   from_path = 0;
   exit_status = 1;

   // The prompt on screen.
   print(prompt);

   if (read_args(&argc, args, MAXARGS, &eof) && argc > 0)
   {
      /**
       * Every command is in the path of the program, and it is accessed through
       * a loop and by changing the path to it.
       */
      for (command = 0; command < NUMCOMMANDS; command++)
      {
         if (!strcmp(args[0], path[command]))
         {
            if (!strcmp(args[0], "cd"))
            {
               // CD command.
               if (argc > 1)
               {
                  cd(args[1]);
               }
               else
               {
                  cd(root_dir);
               }
            }
            else if (!strcmp(args[0], "exit"))
            {
               // If exit written, then, change of state.
               // exit_game() call is then called outside the shell.
               exit_status = true;
               break;
            }
            else
            {
               args[0] = concat(concat(root_dir, "/bin/"), path[command]);
            }

            from_path = 1;
            break;
         }
      }

      // On exit, break the game loop.
      if (exit_status)
      {
         state = GAME_OVER_EXIT;
      }
      else
      {
         /**
          * Error control is done independently, in every child process.
          * Terminal has nothing to do with errors from other processes.
          * 
          * Instead, the errors may come if the shell tries to exec. something
          * that is not a command, nor an executable file.
          */
         if (from_path || !strncmp("./", args[0], 2))
         {
            status = execute(argc, args);
         } else {
            printerr("There must be something wrong with you, I guess.");
         }
      }
   }

   if (eof)
   {
      exit(EXIT_SUCCESS);
   }
}

int main()
{
   // 1. Set game state to configuration state, and deal with signal handling.
   state = CONFIG_TERM;
   setup_signals();

   do
   {
      switch (state)
      {
      case CONFIG_TERM:
         setup();
         state = INIT_MENU;
         break;

      case INIT_MENU:
         // Initial menu.
         do
         {
            print_menu();
         } while (getchar() != ENTER_KEY);

         // If ENTER_KEY is pressed, then, go to CHOOSE_MENU_OPTIONS.
         state = CHOOSE_MENU_OPTIONS;
         break;

      case CHOOSE_MENU_OPTIONS:
         // Choose menu options.
         chosen_option = 0;

         do
         {
            print_menu_options(chosen_option);
            scanf("%d", &chosen_option);
         } while (chosen_option <= 0 && chosen_option > 3);

         // Enter the game :)
         switch (chosen_option)
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
         shell();

         break;

      case GAME_OVER_EXIT:
         exit_game();
         state = CONFIG_TERM;
         break;
      }
   } while (true);

   return EXIT_SUCCESS;
}
