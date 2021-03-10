// Answer Shell (ansshell)

// Mod: David Cuenca Marcos, 2021/03/09

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
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int execute(int argc, char *argv[])
{
   int pid = fork();
   int status;

   switch (pid)
   {
   case -1:
      return 1;   // Error on creating the child process.
   
   case 0:        // Child process' program.
      execv(argv[0], argv);
      break;

   default:       // Parent process.
      wait(&status);
      return status;
   }
}

/**
 * @brief Main body of the application.
 * 
 * @return int 
 */
int main ()
{
   char *Prompt = "\x1b[31mansshell\x1b[0m> ";
   char *exec_error = "\x1b[31m **!! Execution error. Program couldn't be executed. !!** \x1b[0m\n";

   int eof = 0;
   int argc;
   int status;
   int buff;
   char *args[MAXARGS];

   while (1) {
      buff = write(0, Prompt, strlen(Prompt));

      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0) {
         status = execute(argc, args);

         if (status == 1) {
            write(2, exec_error, strlen(exec_error));
            break;
         }
      }

      if (eof) exit(0);
   }

   return 0;
}
