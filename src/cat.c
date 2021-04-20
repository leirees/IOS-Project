/**
 * @file cat.c
 * @author Mikel Aristu, David Cuenca
 * @brief The command used to read files.
 * @version 0.1
 * @date 2021-03-25
 *
 * @copyright Copyright (c) 2021
 */

#include "headers/cat.h"

int main(int argc, char *argv[])
{
   if(argc == 2)
   {
      // Open the file in read-only mode.
      int file_descriptor = open(argv[1], O_RDONLY);
      char *ch;

      // If there is any error when trying to open the file.
      if (file_descriptor < 0)
      {
         printerr("Error while opening the file.");
         exit(EXIT_FAILURE);
      }

      // Read while it has more lines, else, stop and close the file.
      while(read(file_descriptor, ch, 1) != 0) 
      {
         write(1, ch, 1);
      }
      
      close(file_descriptor);
   }
   else
   {
      // If the command is used incorrectly, it will teach the user how to use it.
      println("Usage: cat file_name");
   }

   return 0;
}