/**
 * @file cp.c
 * @author Mikel Aristu, David Cuenca, Team 2.2
 * @brief cp command to copy files
 * @version 0.2
 * @date 2021-04-23
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
#include <errno.h>

int main(int argc, char *argv[])
{
    int origin, end, oread, owrite;
    
    char *buffer[1024];
    char *err_title = THE_SYSTEM;
    char *err;

    if (argc == 3)
    {
        origin = open(argv[1], O_RDONLY);
        
        if (origin < 0)
        {
            printerr("Error opening the file.", err_title);
            exit(EXIT_FAILURE);
        }

        end = open(argv[2], O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

        if (end < 0)
        {
            err = (char *)malloc(strlen("Error opening file %s errno = %d") + strlen(argv[2]) + sizeof(errno));
            sprintf(err, "Error opening file %s errno = %d", argv[2], errno);
            printerr(err, err_title);
            _exit(EXIT_FAILURE);
        }

        oread = read(origin, buffer, sizeof(buffer));

        while (oread > 0)
        {
            if (write(end, buffer, oread) != oread)
            {
                err = (char *)malloc(strlen("Error in writing data to %s") + strlen(argv[2]));
                sprintf(err, "Error in writing data to %s", argv[2]);
                printerr(err, err_title);
                _exit(EXIT_FAILURE);
            }

            oread = read(origin, buffer, sizeof(buffer));
        }
    }
    else
    {
        printerr("Revise your notes. Usage: cp file new_file.", err_title);
    }
    
    _exit(EXIT_SUCCESS);
}