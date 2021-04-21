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
#include "headers/global_variables.h"

struct termios saved_glindos;
struct termios config_glindos;

void setup_signals()
{
   // Process signals SIGINT and SIGTSTP, with particular behaviors.
   signal(SIGINT, signal_handler);
   signal(SIGTSTP, signal_handler);
}

void setup_global_variables()
{
   // Initialise global variables.
   // FLAGS
   exit_status = 0;
   // PID
   child_pid = -1;
   parent_pid = 0;
   // Fail counter.
   fails = 0;
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

int main()
{
   // Begin configuring the signal handing.
   setup_signals();

   // First, set the state of the game to config.
   STATE = CONFIG_TERM;

   // Declare local variables.
   __INT8_TYPE__ from_path;
   __INT8_TYPE__ command;

   // Command path.
   char *PATH[NUMCOMMANDS] = {"cat", "cd", "cp", "exit", "grep", "help", "ls", "mv", "pwd", "stee", "touch", "help", "man"};
   
   // Root directory.
   char *root_dir = getcwd((char *) NULL, 0);

   // Arguments for the commands.
   char *args[MAXARGS];
   int argc, status, buff;
   int eof = 0;

   // Prompt design.
   char *prompt_name = "GlindOS";
   char *prompt = concat(concat(ANSI_COLOR_GREEN, prompt_name), concat(ANSI_COLOR_RESET, "$ "));
   
   // MENU:
   do
   {
      print_menu();
   } while (getchar() != 10);
   
   while (1)
   {
      switch (STATE)
      {
      case CONFIG_TERM:
         setup_global_variables();
         STATE = INIT_MENU;
         break;
      
      default:
         break;
      }

      // Set child pid to -1, in order to remove processes.
      child_pid = -1;

      // The prompt on screen.
      print(prompt);

      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0)
      {
         /**
          * Every command is in the path of the program, and it is accessed through
          * a loop and by changing the path to it.
          */
         
         from_path = 0;
         exit_status = 1;

         for (command = 0; command < NUMCOMMANDS; command++) 
         {
            if (!strcmp(args[0], PATH[command]))
            {
               if (!strcmp(args[0], "cd"))
               {
                  // In case of CD, since it is a function, we only need to exec. it.
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
                  exit_status = exit_game();
                  break;
               }
               else
               {
                  args[0] = concat(concat(root_dir, "/bin/"), PATH[command]);
               }
               
               from_path = 1;
               break;
            }
         }

         // On exit, break the game loop.
         if (!exit_status)
         {
            return EXIT_SUCCESS;
         }

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
         }
      }

      if (eof)
      {
         exit(EXIT_SUCCESS);
      }
   }

   return EXIT_SUCCESS;
}
