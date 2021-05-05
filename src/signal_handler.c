#include "headers/signal_handler.h"
#include "headers/characters/character.h"

void signal_handler(int sig)
{
   char *err_title = THE_SYSTEM;
   char *glinda = GLINDA;

   println("");

   switch (sig)
   {
   case SIGINT:
      if (child_pid < 0)
      {
         exit_game();
         _exit(0);
      }
      else
      {
         
         speak_character(glinda, "Oh, are you abandonning this reality this way, aren't you?");
         speak_character(glinda, "Then, I'm afraid there must be something wrong with you, player.");
         do {

         } while (getchar() != ENTER_KEY);
         
         kill(child_pid, SIGINT);
         _exit(0);
      }
      break;

   case SIGTSTP:
      printerr("Hey! STOP IT NOW //////#!@@@@@ I'm the master here!!!· >:(", err_title);
      break;
   }

   free(err_title);
   free(glinda);
}