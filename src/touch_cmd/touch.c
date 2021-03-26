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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/**
* @brief This void method will call to the open function. In case of error, the open system call will return -1 and an error message will appear.
* @param f_name that will be the wanted file name to be created.
* @param flags that will be the flags of the system call.
* @param modes that will be the permissions of the file created.
*/
 void _touch(char *f_name, char flags, int modes){
    int fd;
    fd = open(f_name, flags, modes);
    if(fd==-1){
        printf(" touch was failed - errno =(%d) \n",errno);
    }else{
        printf(" touch executed successfully\n");
    }
 }

/**
* @brief The main loop of the program.
*
* @param argc argument counter.
* @param argv argument vector.
* @return 0 if it is executed correctly.
*/
 int main(int argc, char *argv[]){
     if (argc<=1 || argc>=3){
        //If the command is used incorrectly, it will teach the user how to use it.
        write(2, "Usage: touch file_name\n", 22);

     }else if(argc==2){
        //Explanation of modes:
        //S_IRWXU: 00700 user (the file owner) has read, write and execute permission.
        //S_IRUSR: 00400 user has read permission.
        //S_IRGRP: 00040 group has read permission00040 group has read permission.
        //S_IROTH: 00004 others have read permission.
        _touch(argv[1], O_CREAT, S_IRWXU|S_IRUSR|S_IRGRP|S_IROTH);
     }
     return 0;
 }
