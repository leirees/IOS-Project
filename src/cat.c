/**
 * @file cat.c
 * @author Mikel Aristu, David Cuenca, Team 2.2
 * @brief The command used to read files.
 * @version 0.2
 * @date 2021-05-04
 * @copyright Copyright (c) 2021
 */

#include "headers/cat.h"
#include "headers/characters/character.h"

int main(int argc, char *argv[])
{
   char ch[30] = "";
   char *err_sys = THE_SYSTEM;

   if (argc == 2)
   {
      // Open the file in read-only mode.
      int file_descriptor = open(argv[1], O_RDONLY);

      // If there is any error when trying to open the file, show the error.
      if (file_descriptor < 0)
      {
         printerr("Error while opening the file.", err_sys);
         exit(EXIT_FAILURE);
      }
      printf("The contents of the file %s are:\n", argv[1]);

      // Read while it has more lines, else, stop and close the file.
      while(read(file_descriptor, ch, 1) != 0)
      {
         write(1, ch, 1);
      }
      close(file_descriptor);
   }
   else
   {
      // If the command is used incorrectly, it will teach the player how to use it.
      printerr("No, no, no. Usage: cat file_name. Revise your notes, please.", err_sys);
   }

   exit(EXIT_SUCCESS);
}