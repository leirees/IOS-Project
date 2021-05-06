#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"
#include "headers/exit.h"

#include <signal.h>
#include <unistd.h>

void signint_parent(int sig) {
   char *glinda = GLINDA;
   speak_character(glinda, "Oh, are you abandonning this reality this way, aren't you?");
   speak_character(glinda, "Then, I'm afraid there must be something wrong with you, player.");
   _exit(127);
}

void signint_child(int sig) {
   char *glinda = GLINDA;
   speak_character(glinda, "Do you really want to exit the game, honey?");
   speak_character(glinda, "I think you don't, >:)");
}

void signstp(int sig) {
   char *err_title = THE_SYSTEM;
   printerr("Hey! STOP IT NOW!!", err_title);
}