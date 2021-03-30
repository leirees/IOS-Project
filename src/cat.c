/**
 * @file cat.c
 * @author Mikel Aristu
 * @brief The command used to read files.
 * @version 0.1
 * @date 2021-03-25
 *
 * @copyright Copyright (c) 2021
 */

#include "headers/cat.h"

int main(int argc, char *argv[])
{
   if (argc <= 1 || argc >= 3)
   {
        // If the command is used incorrectly, it will teach the user how to use it.
        write(2, "Usage: cat file_name\n", strlen("cat file_name"));
        printf("\n");
   }
   else if(argc == 2)
   {
      char ch;
      FILE *fp; // File pointer of the file.

      fp = fopen(argv[1], "r"); // Open the file in read mode.

      // If there is any error when trying to open the file.
      if (fp == NULL)
      {
         write(2,"Error while opening the file.\n",strlen("Error while opening the file.\n"));
         exit(EXIT_FAILURE);
      }
      
      printf("The contents of %s file are:\n", argv[1]);

      // fgetc() returns EOF when arrives the end of the file.
      // Read while it has more lines, else, stop and close the file.
      while((ch = fgetc(fp)) != EOF) 
      {
         printf("%c", ch); // Print each line.
      }
      
      fclose(fp);
   }

   return 0;
}