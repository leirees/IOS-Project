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

    if (argc < 3 || argc >3){
        printf("Usage:\n cp file new_file\n");
   }else{

    firstFD = open(argv[1], O_RDONLY);
    if (firstFD == -1){
        write(2,"Error opening the file.",strlen("Error opening the file."));
    }

    endFD = open(argv[2], O_RDWR | O_CREAT, S_IWUSR | S_IRUSR  | S_IRGRP | S_IROTH);
    if (endFD == -1)
    {
        printf("Error opening file %s errno = %d", argv[2], errno);
        exit(EXIT_FAILURE);
    }

    while ((oread = read(firstFD, buffer, sizeof(buffer))) > 0)
        if(write(endFD,buffer,oread)!=oread){
           printf("Error in writing data to %s",argv[2]);
        }
    }
    return 0;
}