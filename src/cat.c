/**
 * @file cat.c
 * @author Mikel Aristu, David Cuenca, Team 2.2
 * @brief The command used to read files.
 * @version 0.1
 * @date 2021-03-25
 *asdas
 * @copyright Copyright (c) 2021
 */

#include "headers/cat.h"
#include "headers/characters/character.h"

int main(int argc, char *argv[])
{
   char ch[30] = "";
   char str[80];
   char *err_sys = THE_SYSTEM;
   ssize_t write_buff;

   if (argc == 2)
   {
      int bytes_read = 0;

      // Open the file in read-only mode.
      int file_descriptor = open(argv[1], O_RDONLY);

      // If there is any error when trying to open the file.
      if (file_descriptor < 0)
      {
         printerr("Error while opening the file.", err_sys);
         exit(EXIT_FAILURE);
      }

      // Read while it has more lines, else, stop and close the file.
      do
      {
         bytes_read = (file_descriptor, ch, MAXLINE);
         sprintf(str, "Bytes read: %ld", bytes_read);
         print(str);
      } while (bytes_read > 0);

      close(file_descriptor);
   }
   else
   {
      // If the command is used incorrectly, it will teach the user how to use it.
      printerr("No, no, no. Usage: cat file_name. Revise your notes, please.", err_sys);
   }

   exit(EXIT_SUCCESS);
}