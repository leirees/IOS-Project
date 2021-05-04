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
   int file_descriptor;
   ssize_t write_buff, bytes_read;

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
         free(err_sys);
         exit(EXIT_FAILURE);
      }
      printf("The contents of the file %s are:\n", argv[1]);

      // Read while it has more lines, else, stop and close the file.
      while(read(file_descriptor, ch, 1) != 0)
      {
         bytes_read = read(file_descriptor, ch, 1);
         print(ch);
      } while (bytes_read > 0);

      close(file_descriptor);
   }
   else
   {
      // If the command is used incorrectly, it will teach the player how to use it.
      printerr("No, no, no. Usage: cat file_name. Revise your notes, please.", err_sys);
      char *glinda = GLINDA;
      speak_character(glinda, "Please, remember to go to class, player. It is good for you, sweety.");
      free(glinda);
   }

   free(err_sys);
   exit(EXIT_SUCCESS);
}