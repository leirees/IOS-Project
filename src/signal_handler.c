#include "headers/signal_handler.h"
#include "headers/characters/character.h"

void signal_handler(int sig)
{
   char *err_title = THE_SYSTEM;
   char *glinda = GLINDA;

   switch (sig)
   {
   case SIGINT:
      if (child_pid < 0)
      {
         exit_game();
      }
      else
      {
         speak_character(glinda, "Oh, are you abandonning this reality this way, aren't you?");
         speak_character(glinda, "Then, I'm afraid there must be something wrong with you, player.");
         kill(child_pid, SIGINT);
      }
      break;

   case SIGTSTP:
      printerr("Hey! STOP IT NOW //////#!@@@@@ I'm the master here!!!· >:(", err_title);
      break;
   }

   free(err_title);
   free(glinda);
}