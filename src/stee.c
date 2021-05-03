/**
 * @file stee.c
 * @author Mikel Aristu
 * @brief The command that saves the name of the player.
 * @version 0.4
 * @date 2021-04-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "headers/stee.h"
#include "headers/characters/character.h"

int stee()
{
   char *err_title = THE_SYSTEM;
   char *name;
   int fd;

   ssize_t buff;

   // Try to open the file.
   fd = open(concat(root_dir, "config/.player/.ref"), O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

   if (fd == -1)
   {
      printerr("Oh! I cannot access that file!", err_title);
      return EXIT_FAILURE;
   }

   speak_charwtitle(&glinda, "What's your name, darling?", 0);
   scanf("%s", name);

   char *ans;
   sprintf(ans, "Hello %s, I'm glad of hearing from you!", name);
   speak_charwtitle(&glinda, ans, 1);
   free(ans);

   // Record name.
   buff = write(fd, name, strlen(name));
   close(fd);
   free(err_title);
   return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
   char *err_title = THE_SYSTEM;

   if (argc != 1)
   {
      printerr("Error! You don't even know how to write you name, you ape? OK, write <<stee \"your_name\">>", err_title);
      return EXIT_FAILURE;
   }

   free(err_title);
   return stee() ? EXIT_FAILURE : EXIT_SUCCESS;
}