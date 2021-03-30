/**
 * @file touch.c
 * @author Mikel Aristu
 *
 * @brief The command used to create items.
 *
 * @version 0.2
 * @date 2021-03-24
 *
 * @copyright Copyright (c) 2021
 */

#include "headers/touch.h"

void _touch(char *f_name, char flags, int modes)
{
    int fd;
    fd = open(f_name, flags, modes);
    
    if (fd == -1)
    {
        printf(" touch has failed - errno =(%d) \n", errno);
    }
    else
    {
        printf(" touch executed successfully\n");
    }
}

int main(int argc, char *argv[]){
    if (argc == 2)
    {
        //Explanation of modes:
        //S_IRWXU: 00700 user (the file owner) has read, write and execute permission.
        //S_IRUSR: 00400 user has read permission.
        //S_IRGRP: 00040 group has read permission.
        //S_IROTH: 00004 others have read permission.
        _touch(argv[1], O_CREAT, S_IRWXU|S_IRUSR|S_IRGRP|S_IROTH);
    }
    else
    {
        //If the command is used incorrectly, it will teach the user how to use it.
        write(2, "Usage: touch file_name\n", 22);
    }

    return 0;
 }
