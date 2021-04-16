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

int pid;
char *args[MAXARGS];

void signal_handler(int sig)
{
   switch (sig)
   {
   case SIGINT:
      if (pid != 0) 
      {
         kill(pid, SIGKILL);
      }
      else
      {
         println("I think you have missed something, somewhere...");
      }
      break;

   case SIGTSTP:
      args[0] = "bin/exit";
      execute(1, args);
      break;

   default:
      break;
   }
}

int read_args(int* argcp, char* args[], int max, int* eofp)
{
   static char cmd[MAXLINE];
   char* cmdp;
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
   case 1 : 
      // Correct reading
      cmd[i+1]='\0';     
      break;

   case 0 : 
      // End of file
      *eofp = 1;        
      return EXIT_SUCCESS;
   
   case -1 : 
      // Reading failure
      *argcp = -1;
      fprintf(stderr,"Reading failure \n");
      return EXIT_SUCCESS;
      
   case -2 : 
      // Line too long
      *argcp = -1;     
      fprintf(stderr,"Line too long -- removed command\n");
      return EXIT_SUCCESS;
   }

   // Analyzing the line
   cmdp = cmd;
   for (i = 0; i < max; i++) 
   {  
      args[i] = strtok(cmdp, " \t\n");
      /* to show every argument */
      if (args[i] == (char*) NULL) 
         break;
      
      cmdp = NULL;
   }

   if (i >= max) 
   {
      fprintf(stderr,"Too many arguments -- removed command\n");
      return 0;
   }
   
   *argcp = i;
   return EXIT_FAILURE;
}

int execute(int argc, char *argv[])
{
   int status;
   pid = fork();

   switch (pid)
   {
   case -1:
      // Error on creating the child process.
      return 1;   
   
   case 0:  
      // Child process' program.
      // Execute the give command, if possible.
      execvp(argv[0], argv);
      break;

   default: 
      // Parent process execution.
      // Wait until child process terminates.
      wait(&status);
      return status;
   }
}

int main ()
{
   int argc, status, buff;
   int eof = 0;

   unsigned int command;

   /* PROMPT AND MESSAGES */
   char *prompt_name = "GlindOS";
   char *prompt = concat(concat(ANSI_COLOR_GREEN, prompt_name),  concat(ANSI_COLOR_RESET, "\"> "));
   
   // PATH
   char *PATH[NUMCOMMANDS] = {"cat", "cd", "cp", "exit", "grep", "help", "ls", "mv", "pwd", "stee", "touch", "help", "man"};
   unsigned int fromPath = 0; // In order to know if the command is in the path or not.

   // Ignore Ctrl+C as SIGINT
   signal(SIGINT, signal_handler);
   signal(SIGTSTP, signal_handler);

   while (1) {
      // Set pid to 0, in order to kill his child processes.
      pid = 0;

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
               args[0] = concat("bin/", PATH[command]);
               fromPath = 1;
            }
            else
            {
               command++;
            }
         } while(!fromPath && command < NUMCOMMANDS);

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
