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
   int pid = fork();

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
   int argc;
   int status;
   int buff;
   int eof = 0;

   char *args[MAXARGS];

   /* PROMPT AND MESSAGES */
   char *prompt_name = "GlindOS";
   char *prompt = concat(concat(ANSI_COLOR_GREEN, prompt_name),  concat(ANSI_COLOR_RESET, "\"> "));
   char *exec_error = "**!! Execution error. Program couldn't be executed. !!**";


   // MAIN LOOP OF THE PROGRAM.
   while (1) {
      // The prompt on screen.
      print(prompt);

      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0) 
      {
         // Command reading: optimize for reading a directory and executing the commands
         // there are.
         // TODO: optimize...
         if      (!strcmp(args[0], "cat")) 
         {
            args[0] = "bin/cat";
         }
         else if (!strcmp(args[0], "cd"))
         {
            // Make CD.
            cd(argc, args);
         }
         else if (!strcmp(args[0], "cp"))
         {
            args[0] = "bin/cp";
         } 
         else if (!strcmp(args[0], "exit"))
         {
            args[0] = "bin/exit";
         }
         else if (!strcmp(args[0], "grep"))
         {
            args[0] = "bin/grep";
         }
         else if (!strcmp(args[0], "help"))
         {
            args[0] = "bin/help";
         }
         else if (!strcmp(args[0], "ls"))
         {
            args[0] = "bin/ls";
         }
         else if (!strcmp(args[0], "mv"))
         {
            args[0] = "bin/mv";
         }
         else if (!strcmp(args[0], "pwd"))
         {
            args[0] = "bin/pwd";
         }
         else if (!strcmp(args[0], "stee"))
         {
            args[0] = "bin/stee";
         }
         else if (!strcmp(args[0], "touch"))
         {
            args[0] = "bin/touch";
         }
         else
         {
            printerr("Say something useful, you clod... Mehewww");
         }

         // Error control is done independently, in every child process.
         // Terminal has nothing to do with errors from other processes.
         status = execute(argc, args);
      } else {
         printerr("Say something useful, you clod... Mehewww");
      }

      if (eof) 
      {
         exit(EXIT_SUCCESS);
      }
   }

   return EXIT_SUCCESS;
}
