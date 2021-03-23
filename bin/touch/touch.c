/**
 * @file touch.c
 * @author Mikel Aristu
 *
 * @brief The command used to create items.
 *
 * @version 0.1
 * @date 2021-03-23
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

/**
* @brief This void method will call to the open function.
* @param f_name that will be the wanted file name to be created.
*/
 void _touch(char *f_name, int RDWR){
     creat(f_name, RDWR); //The open function will be executed always to read and write.
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
        _touch(argv[1], O_RDWR);
     }
     return 0;
 }