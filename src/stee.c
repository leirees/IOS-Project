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

#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int stee()
{
   char *err_title = THE_SYSTEM;
   char *glinda = GLINDA;

   char *name;
   int fd;

   ssize_t buff;

   // Try to open the file.
   fd = open("name.c", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

   if (fd == -1)
   {
      printerr("Oh! I cannot access that file!", err_title);
      return EXIT_FAILURE;
   }

   speak_character(glinda, "What's your name, darling?");
   scanf("%s", name);

   // Welcome the user to the game.
   char *ans = (char *) malloc(strlen("Hello %s, I'm glad of hearing from you!") + strlen(name));
   sprintf(ans, "Hello %s, I'm glad of hearing from you!", name);
   speak_character(glinda, ans);


   // Record name.
   buff = write(fd, name, strlen(name));
   close(fd);

   return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
   char *err_title = THE_SYSTEM;

   if (argc != 2)
   {
      printerr("Error! You don't even know how to write you name, you ape? OK, write <<stee \"your_name\">>", err_title);
      return EXIT_FAILURE;
   }
   
   return stee() ? EXIT_FAILURE : EXIT_SUCCESS;
}