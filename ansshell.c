/**
 * @file ansshell.c
 * @author Lecturer and Team 2.2
 * 
 * @brief Answer shell for IOS Project. (REDO, better) 
 * 
 * @version 0.1
 * @date 2021-03-16
 * 
 * @copyright Copyright (c) 2021
 */
//////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/wait.h>

#define error(a) {perror(a); exit(1);};
#define MAXLINE 200
#define MAXARGS 20

/////////// reading commands:

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

///////////////////////////////////////

/**
 * @brief Execute a process, given a command and its arguments.
 * 
 * @param argc Argument counter: the number of arguments that are passed (int, >= 1).
 * @param argv Argument vector: the arguments that are passed (char*, len(char*) >= 1)
 * @return int -1 if error creating the process, 1 if error while executing the process or 0 if ok.
 */
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
      execv(argv[0], argv);
      break;

   default: 
      // Parent process execution.
      // Wait until child process terminates.
      wait(&status);
      return status;
   }
}

/**
 * @brief Main body of the application.
 *
 * @return int 0 iff ok.
 */
int main ()
{
   char *prompt = "\x1b[31mansshell\x1b[0m> ";
   char *exec_error = "\x1b[31m **!! Execution error. Program couldn't be executed. !!** \x1b[0m\n";

   int argc;
   int status;
   int buff;

   int eof = 0;

   char *args[MAXARGS];

   while (1) {
      // The prompt on screen.
      buff = write(1, prompt, strlen(prompt));

      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0) 
      {
         // TEMPORAL: exit early
         if (!strcmp(args[0], "exit")) 
         {
            args[0] = "./bin/exit/exit";
            status = execute(1, args);
            return status;
         }
         
         // If possible, run the command and return the output.
         status = execute(argc, args);

         if (status == 1) 
         {
            write(2, exec_error, strlen(exec_error));
            break;
         }
      }

      if (eof) 
      {
         exit(0);
      }
   }

   return 0;
}
