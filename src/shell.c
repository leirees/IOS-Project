/**
 * @file ansshell.c
 * @author IOS Lecturer, 2.2 Team
 * @brief Implementation of shell.
 * @version 0.1
 * @date 2021-03-26
 * 
 * @copyright Copyright (c) 2021
 */

#include "shell.h"

int read_args(int* argcp, char* args[], int max, int* eofp)
{
   static char cmd[MAXLINE];
   char* cmdp;
   int ret,i;

   *argcp = 0;
   *eofp = 0;

   i=0;
   
   while ((ret=read(0,cmd+i,1)) == 1) {
      if (cmd[i]=='\n') break;  // correct line
      i++;

      if (i >= MAXLINE) {
         ret=-2;                // line too long
         break;
      }
   }
   
   switch (ret)
   {
     case 1 : cmd[i+1]='\0';    // correct reading 
         break;
     case 0 : *eofp = 1;        // end of file
         return 0;
         break;
     case -1 : *argcp = -1;     // reading failure
         fprintf(stderr,"Reading failure \n");
         return 0;
         break;
     case -2 : *argcp = -1;     // line too long
         fprintf(stderr,"Line too long -- removed command\n");
         return 0;
         break;
   }

   // Analyzing the line
   cmdp= cmd;
   for (i=0; i<max; i++) {  /* to show every argument */
      if ((args[i]= strtok(cmdp, " \t\n")) == (char*)NULL) break;
      cmdp= NULL;
   }

   if (i >= max) {
      fprintf(stderr,"Too many arguments -- removed command\n");
      return 0;
   }
   
   *argcp= i;
   return 1;
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
         if (!strcmp(args[0], "exit")) 
         {
            args[0] = "exit_cmd/exit";
         } 
         else if (!strcmp(args[0], "ls"))
         {
            args[0] = "ls_cmd/ls";
         }
         else if (!strcmp(args[0], "pwd"))
         {
            args[0] = "pwd_cmd/pwd";
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
         exit(0);
      }
   }

   return 0;
}
