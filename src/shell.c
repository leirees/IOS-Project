/**
 * @file ansshell.c
 * @author IOS Lecturer, 2.2 Team
 * @brief Implementation of shell.
 * @version 0.1
 * @date 2021-03-10
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/shell.h"
#include "headers/characters/character.h"

// Character's definition.
// Main character
player dorothy;

character scarecrown;
character tinman;
character lion;

character_with_title glinda;
character_with_title ofelia;

// Secondary character
character admin;
character dog;

character_with_title gertrudis;
character_with_title jasmine;

// Extras
character trees;
character guardian;
character ghost;

// State...
static int8 status;
static int8 last_state;

void setup_signals()
{
   signal(SIGINT, signal_handler);
   signal(SIGTSTP, signal_handler);
}

void setup_game()
{
   // Root dir
   root_dir = getcwd((char *)NULL, 0);

   // PID
   parent_pid = getpid();
   child_pid = -1;

   /* Characters creation */
   // Companion creation
   char *scarecrown_name = SCARECROWN;
   char *tinman_name = TINMAN;
   char *lion_name = LION;

   create_character(&scarecrown, scarecrown_name, false, false, true);
   create_character(&lion, lion_name, false, false, true);
   create_character(&tinman, tinman_name, false, false, true);

   // Witches creation
   char *short_title_glinda = SHORT_GLINDA;
   char *short_title_ofelia = SHORT_OFELIA;
   char *short_title_gertrudis = SHORT_GERTRUDIS;
   char *short_title_jasmine = SHORT_JASMINE;
   char *title_glinda = GLINDA;
   char *title_ofelia = OFELIA;
   char *title_gertrudis = GERTRUDIS;
   char *title_jasmine = JASMINE;

   create_witch(&glinda, "Glinda", short_title_glinda, title_glinda, false);
   create_witch(&ofelia, "Ofelia", short_title_ofelia, title_ofelia, true);
   create_witch(&gertrudis, "Gertrudis", short_title_gertrudis, title_gertrudis, true);
   create_witch(&jasmine, "Jasmine", short_title_jasmine, title_jasmine, false);

   // Secondary characters
   char *admin_name = ADMIN;
   create_character(&admin, admin_name, true, false, false);

   char *dog_name = DOG;
   create_character(&dog, dog_name, false, false, false);

   // Extras
   char *trees_name = TREES;
   char *ghost_name = GHOST;
   char *guardian_name = GUARDIAN;

   create_character(&trees, trees_name, false, false, false);
   create_character(&ghost, ghost_name, true, false, false);
   create_character(&guardian, guardian_name, false, false, false);
}

int read_args(int16 *argcp, char *args[], int max, bool *eofp)
{
   char cmd[MAXLINE];
   char *cmdp;
   int ret, i = 0;

   *argcp = 0;
   *eofp = 0;

   do
   {
      ret = read(0, cmd + i, 1);
      if (cmd[i] == '\n')
      {
         // Correct line
         break;
      }
      i++;

      if (i >= MAXLINE)
      {
         // Line too long
         ret = -2;
         break;
      }
   } while (ret == 1);

   switch (ret)
   {
   case 1:
      // Correct reading
      cmd[i + 1] = '\0';
      break;

   case 0:
      // End of file
      *eofp = 1;
      return EXIT_SUCCESS;

   case -1:
      // Reading failure
      *argcp = -1;
      fprintf(stderr, "Reading failure \n");
      return EXIT_SUCCESS;

   case -2:
      // Line too long
      *argcp = -1;
      fprintf(stderr, "Line too long -- removed command\n");
      return EXIT_SUCCESS;
   }

   // Analyzing the line
   cmdp = cmd;
   for (i = 0; i < max; i++)
   {
      args[i] = strtok(cmdp, " \t\n");
      /* to show every argument */
      if (args[i] == (char *)NULL)
         break;

      cmdp = NULL;
   }

   if (i >= max)
   {
      fprintf(stderr, "Too many arguments -- removed command\n");
      return 0;
   }

   *argcp = i;
   return EXIT_FAILURE;
}

int execute(int argc, char *argv[])
{
   child_pid = fork();

   switch (child_pid)
   {
   case -1:
      // Error in fork() (not so common)
      return EXIT_FAILURE;

   case 0:
      // Child process
      execvp(argv[0], argv);
      break;

   default:
      // Parent process.
      wait(NULL);
      break;
   }

   return EXIT_SUCCESS;
}

int shell()
{
   char *err_title = THE_SYSTEM;
   char *game_dir = concat(root_dir, "/config/.gamedir");
   char *prompt = concat(concat(ANSI_COLOR_BLUE, concat(PROMPT_NAME, ANSI_COLOR_RESET)), concat(concat("[", concat(game_dir, "]")), "$"));

   // Change the official dir to the root dir.
   // chdir((const char *)root);
   char *args[MAXARGS];
   int16 argc;
   bool eof;

   u8 command;

   while (1)
   {
      // Print the prompt on screen.
      print(prompt);

      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0)
      {
         DIR *path = opendir(concat(root_dir, "/bin"));

         if (!path)
         {
            if (errno == ENOENT)
            {
               printerr("Oh, oh... NO root dir!", err_title);
            }
            else
            {
               printerr("Oh, oh... cannot open root dir!", err_title);
            }
         }

         struct dirent *cmd;

         while ((cmd = readdir(path)) != NULL)
         {
            if (!strncmp(cmd->d_name, args[0], 20))
            {
               args[0] = concat("/bin/", args[0]);
               status = execute(argc, args);
               break;
            }
         }

         closedir(path);

         if (!strcmp(args[0], "cd"))
         {
            if (argc == 2)
            {
               // CD command, to some place.
               cd(args[1]);
               game_dir = getcwd((char *)NULL, 0);
            }
            else if (argc == 1)
            {
               // Else, go to the game root dir.
               cd(root_dir);
               game_dir = concat(root_dir, "/config/.gamedir");
            }
            else
            {
               printerr("Oh, oh... CD not OK!", err_title);
            }
         }
         else if (!strcmp(args[0], "exit"))
         {
            // EXIT command.
            last_state = state;
            state = GAME_OVER_EXIT;
         }

         // Check commands from outside the path.
         if (!strncmp("./", args[0], 2))
         {
            status = execute(argc, args);
         }
      }

      if (eof)
      {
         return EXIT_FAILURE;
      }
   }

   return EXIT_SUCCESS;
}

int main()
{
   // Setup System Agent: the one that provides its body as the work in which we work.
   u8 option;

   // Setup signals
   print("Setting up signals...");
   setup_signals();
   print("OK\n");

   // 1. Set game state to configuration state, and deal with signal handling.
   state = CONFIG_TERM;

   do
   {
      switch (state)
      {
      case CONFIG_TERM:
         // Setup game and change state.
         println("Setting the game up...");
         setup_game();
         last_state = state;
         println("OK\n");

         state = INIT_MENU;
         break;

      case INIT_MENU:
         // Initial menu: if ENTER_KEY pressed, go to CHOOSE_MENU_OPTIONS.
         println("Initialising game menu. OK");
         println("Press enter to continue...");

         do
         {

         } while (getchar() != ENTER_KEY);

         do
         {
            print_menu();
         } while (getchar() != ENTER_KEY);

         last_state = state;
         state = CHOOSE_MENU_OPTIONS;
         break;

      case CHOOSE_MENU_OPTIONS:
         // Choose menu options.
         option = 0;
         print_menu_options(option);
         scanf("%d", &option);

         if (option)
         {
            print_menu_options(option);

            last_state = state;

            switch (option)
            {
            case 1:
               state = GAME_RUNNING;
               break;

            case 2:
               state = SHOW_SCORES;
               break;

            case 3:
               state = GAME_OVER_EXIT;
               break;
            }
         }

         clear_screen();

         break;

      case GAME_RUNNING:
         shell();
         break;

      case GAME_OVER_EXIT:
         if (exit_game())
         {
            state = last_state;
         }
         else
         {
            if (last_state == GAME_RUNNING)
            {
               state = CONFIG_TERM;
            }
            else if (last_state == CHOOSE_MENU_OPTIONS)
            {
               _exit(EXIT_SUCCESS);
            }
         }
         break;
      }
   } while (true);

   return 0;
}
