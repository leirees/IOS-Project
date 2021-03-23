#include "ansshell.h"

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
      execv(argv[0], argv);
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
   char *prompt = concat(concat(ANSI_COLOR_GREEN, "ansshell"),  "> ");
   char *exec_error = concat(ANSI_COLOR_RED, "**!! Execution error. Program couldn't be executed. !!**");

   int argc;
   int status;

   int buff;

   int eof = 0;

   char *args[MAXARGS];

   while (1) {
      // The prompt on screen.
      // buff = write(1, prompt, strlen(prompt));
      print(prompt);

      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0) 
      {
         // TEMPORAL: exit early
         if (!strcmp(args[0], "exit")) 
         {
            args[0] = "./bin/exit/exit";
            status = execute(1, args);
            return status;
         }
         
         status = execute(argc, args);

         if (status == 1) 
         {
            // Error in stderr.
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
