/**
 * @file cat.c
 * @author Mikel Aristu, David Cuenca, Team 2.2
 * @brief The command used to read files.
 * @version 3
 * @date 2021-05-04
 * @copyright Copyright (c) 2021
 */

#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"

// Syscalls && util
#include <unistd.h>
// Std library
#include <stdlib.h>
#include <stdio.h>
// System flags.
#include <fcntl.h>

int main(int argc, char *argv[])
{
   char *glinda = GLINDA;

   int file_descriptor;
   ssize_t bytes_read;

   char *err_sys = THE_SYSTEM;
   char *ch;

   if (argc == 2)
   {
      // Open the file in read-only mode.
      file_descriptor = open(argv[1], O_RDONLY);

      // If there is any error when trying to open the file.
      if (file_descriptor == -1)
      {
         printerr("Error while opening the file.", err_sys);
         printerr("YOU DON'T EVEN KNOW TO READ!!!", err_sys);

         return 1;
      }

      // Read while it has more lines, else, stop and close the file.
      do
      {
         bytes_read = read(file_descriptor, ch, 1);
         print(ch);
      } while (bytes_read > 0);

      close(file_descriptor);

      return 0;
   }

   // If the command is used incorrectly, it will teach the player how to use it.
   printerr("No, no, no. Usage: cat file_name. Revise your notes, please.", err_sys);
   speak_character(glinda, "Please, remember to go to class, player. It is good for you, sweety.");
   
   return 1;
}