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

pid_t child_pid, parent_pid;

/**
* @brief The menu screen!
*/
void print_menu()
{
   println("***************************************************************");
   println("***************************************************************");
   println("***************************************************************");
   println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
   println("**************|******* THE WIZARD OF OS *******|***************");
   println("**************|                                |***************");
   println("**************|**** \"A wizardry adventure\" ****|***************");
   println("**************|                                |***************");
   println("**************|  \"Hurry up! Toto is waiting!\"  |***************");
   println("**************|                                |***************");
   println("**************|*** Press enter key to begin ***|***************");
   println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
   println("***************************************************************");
   println("***************************************************************");
   println("***************************************************************");
}

/**
 * @brief The options menu!
 */
void print_menu_options()
{
   println("***************************************************************");
   println("***************************************************************");
   println("***************************************************************");
   println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
   println("**************|                                |***************");
   println("**************|  MENU:                         |***************");
   println("**************|   1.  PLAY GAME                |***************");
   println("**************|   2.  SCORE LIST               |***************");
   println("**************|                                |***************");
   println("**************|   X.  EXIT GAME                |***************");
   println("**************|                                |***************");
   println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************");
   println("***************************************************************");
   println("***************************************************************");
   println("***************************************************************");
   print("*** YOUR OPTION IS: ");
}

void signal_handler(int sig)
{
   switch (sig)
   {
   case SIGINT:
      if (child_pid < 0)
      {
         println("");
         println("Glinda, \"The good witch from the North\": Oh, dada.");
         println("Glinda, \"The good witch from the North\": Good bye, dear!");
         
         child_pid = fork();

         if (child_pid == 0) 
         {
            char *smt[1] = {"bin/exit"};
            execvp("bin/exit", smt);
         } else 
         {
            if (child_pid < 0) 
            {
               printerr("Glinda, \"The good witch from the North\": Hmmm... There must be something wrong with my magical wand.");
               println ("Glinda, \"The good witch from the North\": I must revise it as soon as possible.");
            }
            else
            {
               wait(NULL);
            }
         }

      }
      else
      {
         println("");
         println("Glinda, \"The good witch from the North\": Oh, are you abandonning this reality this way, aren't you? ");
         println("Glinda, \"The good witch from the North\": Then, I'm afraid there must be something wrong with you, player.");
         kill(parent_pid, SIGKILL);
      }
      break;

   case SIGTSTP:
      println("Hey! STOP IT >:(");
      break;
   }
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
   // The status to return to the parent.
   int *status;
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
      wait(status);
      return *status;
   }
}

int main()
{
   // Get parent pid, for latter purposes: exit, comparing.
   parent_pid = getpid();

   // Root directory
   char *root_dir = getcwd((char *)NULL, 0);

   // Commands from path
   char *PATH[NUMCOMMANDS] = {"cat", "cd", "cp", "exit", "grep", "help", "ls", "mv", "pwd", "stee", "touch", "help", "man"};

   // In order to know if the command is in the path or not.
   unsigned int fromPath;
   unsigned int command;

   char *args[MAXARGS];
   int argc, status, buff;
   int eof = 0;

   // Prompt design.
   char *prompt_name = "GlindOS";
   char *prompt = concat(concat(ANSI_COLOR_GREEN, prompt_name), concat(ANSI_COLOR_RESET, "$ "));

   // Process signals SIGINT and SIGTSTP, with particular behaviors.
   signal(SIGINT, signal_handler);
   signal(SIGTSTP, signal_handler);

   char begin;

   do
   {
      print_menu();
   } while ((begin = getchar()) != 10);
   

   while (1)
   {
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
         command = 0;
         fromPath = 0;

         do
         {
            if (!strcmp(args[0], PATH[command]))
            {
               if (!strcmp(args[0], "cd"))
               {
                  // In case of CD, since it is a function, we only need to exec. it.
                  cd(args[1]);
               }
               else
               {
                  args[0] = concat(concat(root_dir, "/bin/"), PATH[command]);
               }
               fromPath = 1;
            }
            else
            {
               command++;
            }
         } while (!fromPath && command < NUMCOMMANDS);

         /**
          * Error control is done independently, in every child process.
          * Terminal has nothing to do with errors from other processes.
          * 
          * Instead, the errors may come if the shell tries to exec. something
          * that is not a command, nor an executable file.
          */
         if (fromPath || !strncmp("./", args[0], 2))
         {
            status = execute(argc, args);
         }
         else
         {
            printerr("Say something useful, you clod... Mehewww");
         }
      }

      if (eof)
      {
         exit(EXIT_SUCCESS);
      }
   }

   return EXIT_SUCCESS;
}
