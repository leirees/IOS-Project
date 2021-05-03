/**
 * @file cp.c
 * @author Mikel Aristu
 * @brief cp command to copy files
 * @version 0.2
 * @date 2021-04-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "headers/cp.h"

int main(int argc, char *argv[])
{
    int firstFD, endFD, oread, owrite;
    char *buffer[1024];
    char *err;

    if (argc == 3)
    {
        firstFD = open(argv[1], O_RDONLY);
        if (firstFD == -1)
        {
            printerr("Error opening the file.");
        }

        endFD = open(argv[2], O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
        if (endFD == -1)
        {
            err = (char *) malloc(strlen("Error opening file %s errno = %d") + strlen(argv[2]) + strlen(errno));
            err = "Error opening file %s errno = %d";
            sprintf(err, argv[2], errno);
            printerr(err);
            free(err);
            exit(EXIT_FAILURE);
        }

        while ((oread = read(firstFD, buffer, sizeof(buffer))) > 0)
        {
            if (write(endFD, buffer, oread) != oread)
            {
                err = (char *) malloc(strlen("Error in writing data to %s" + strlen(argv[2])));
                err = "Error in writing data to %s";
                sprintf(err, argv[2]);
                printerr(err);
                free(err);
                exit(EXIT_FAILURE);
            }
        }
    }
    else
    {
        error("Usage:\n cp file new_file\n")
    }
    
    return EXIT_SUCCESS;
}