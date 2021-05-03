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

#include "headers/cp.h"
#include "headers/characters/character.h"

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
            free(err_title);
            exit(EXIT_FAILURE);
        }

        end = open(argv[2], O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

        if (end < 0)
        {
            sprintf(err, "Error opening file %s errno = %d", argv[2], errno);
            printerr(err, err_title);
            free(err_title);
            exit(EXIT_FAILURE);
        }

        oread = read(origin, buffer, sizeof(buffer));

        while (oread > 0)
        {
            if (write(end, buffer, oread) != oread)
            {
                sprintf(err, "Error in writing data to %s", argv[2]);
                printerr(err, err_title);
                free(err_title);
                exit(EXIT_FAILURE);
            }

            oread = read(origin, buffer, sizeof(buffer));
        }
    }
    else
    {
        printerr("Revise your notes. Usage:\n cp file new_file\n", err_title);
    }
    
    return EXIT_SUCCESS;
}