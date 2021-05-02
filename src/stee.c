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

int main(int argc, char *argv[])
{
   FILE *fd;
   char name[25];

   if (argc != 1)
   {
      write(2, "Usage: stee\n", 24);
      exit(1);
   }
   printf("What's your name?\n");
   scanf("%249s", name);
   printf("Hello %s, I'm glad of hearing from you!\n", name);
   
   if((fd = fopen("../config/.player/.ref", "w"))==NULL)
   {
        write(2, "Failed saving your name\n", 23);
        exit(1);
   }

   fprintf(fd, "%s", name);
   fclose(fd);
  
}