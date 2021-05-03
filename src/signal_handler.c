#include "headers/signal_handler.h"

void signal_handler(int sig)
{
   switch (sig)
   {
   case SIGINT:
      if (child_pid < 0)
      {
         exit_game();
      }
      else
      {
         speak_glinda("Oh, are you abandonning this reality this way, aren't you?\n Then, I'm afraid there must be something wrong with you, player.", 0);
         kill(child_pid, SIGINT);
      }
      break;

   case SIGTSTP:
      printerr("Hey! STOP IT NOW //////#!@@@@@ I'm the master here!!!· >:(");
      break;
   }
}