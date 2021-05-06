#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

#include "src/headers/libstring/libstring.h"

#define MAXLINE 200

#define THE_SYSTEM underlined(concat(reversed(concat(ANSI_COLOR_RED, "THE SYSTEM")), ANSI_COLOR_RESET))

// The player
#define PLAYER underlined(concat(concat(ANSI_COLOR_WHITE, bold("The Player")), ANSI_COLOR_RESET))

// Definition of THE WITCHES
// The four witches' titles
#define GLINDA_NAME "Glinda"
#define GLINDA_TITLE ", <<The Good Witch of the NORTH>>"
#define GLINDA_COMPLETE concat(BOLD, underlined(concat(ANSI_COLOR_CYAN, concat(GLINDA_NAME, GLINDA_TITLE))))
#define GLINDA GLINDA_COMPLETE
#define SHORT_GLINDA concat(BOLD, underlined(concat(ANSI_COLOR_CYAN, GLINDA_NAME)))

#define OFELIA_NAME "Ofelia"
#define OFELIA_TITLE ", <<The Most Evil Bad Witch, The Witch of the WEST>>"
#define OFELIA_COMPLETE concat(BOLD, underlined(concat(ANSI_COLOR_RED, concat(OFELIA_NAME, OFELIA_TITLE))))
#define OFELIA OFELIA_COMPLETE
#define SHORT_OFELIA concat(BOLD, underlined(concat(ANSI_COLOR_RED, concat(OFELIA_NAME, ", <<The Most Evil Bad Witch>>"))))

#define GERTRUDIS_NAME "Gertrudis"
#define GERTRUDIS_TITLE ", <<The Evil Witch of the EAST>>"
#define GERTRUDIS_COMPLETE concat(BOLD, underlined(concat(ANSI_COLOR_YELLOW, concat(GERTRUDIS_NAME, GERTRUDIS_TITLE))))
#define GERTRUDIS GERTRUDIS_COMPLETE
#define SHORT_GERTRUDIS concat(BOLD, underlined(concat(ANSI_COLOR_YELLOW, GERTRUDIS_NAME)))

#define JASMINE_NAME "Jasmine"
#define JASMINE_TITLE ", <<The Good Witch of the SOUTH>>"
#define JASMINE_COMPLETE concat(BOLD, underlined(concat(ANSI_COLOR_GREEN, concat(JASMINE_NAME, JASMINE_TITLE))))
#define JASMINE JASMINE_COMPLETE
#define SHORT_JASMINE concat(BOLD, underlined(concat(ANSI_COLOR_GREEN, GERTRUDIS_NAME)))

/* Definition of the COMPANIONS */
// The Three Knights of the Player + DOG
#define SCARECROWN underlined(bold("The Brainless Scarecrown"))
#define TINMAN underlined(bold("The Heartless Tinman"))
#define LION underlined(bold("The Coward Lion"))

// This is Toto, you fellow dog :DD
#define DOG concat(BOLD, underlined("TOTO <<My doge>>"))

/* Definition of EXTRAS */
#define TREES concat(BOLD, underlined("Forest trees"))
#define GUARDIAN concat(BOLD, underlined("Guardian"))
#define GHOST concat(BOLD, underlined("CASPER <<The Friendly Ghost>>"))
#define ADMIN concat(BOLD, underlined("THE ADMIN"))

int main(int argc, char *argv[])
{
    // The current word.
    char *current_word = "";
    // Current line word
    char *current_line = "";
    // The text itself.
    char *lines[MAXLINE];

    size_t line = 0;
    ssize_t buff;

    if (argc != 2)
    {
        perror("ERROR! The command is not that");
        return 1;
    }

    int file_desc = open(argv[1], O_RDONLY);

    if (!file_desc)
    {
        perror("ERROR! The command is not that");
        return 1;
    }

    char *current_char;
    buff = read(file_desc, current_char, 1);

    if (buff == -1)
    {
        perror("ERROR! The command is not that");
        return 1;
    }

    while (buff > 0)
    {
        if (!strcmp(current_word, "Player"))
        {
            current_word = PLAYER;
        }
        else if (!strcmp(current_word, "Badwitch"))
        {
            current_word = OFELIA;
        }
        else if (!strcmp(current_word, "Goodwitch"))
        {
            current_word = GLINDA;
        }
        else if (!strcmp(current_word, "Dog"))
        {
            current_word = DOG;
        }

        if (!strcmp(current_char, " "))
        {
            current_line = strcat(current_line, (const char *)current_word);
            current_word = "";
        }
        else if (!strcmp(current_char, "\n"))
        {
            current_line = strcat(current_line, (const char *)current_word);
            current_word = "";

            lines[line++] = current_line;
            current_line = "";
        }
        else
        {
            strcat(current_word, (const char *)current_char);
        }

        buff = read(file_desc, current_char, 1);
    }

    close(file_desc);

    for (size_t ln = 0; ln < sizeof(lines) / sizeof(lines[0]); ln++)
    {
        printf("%s", lines[ln]);
    }

    return 0;
}