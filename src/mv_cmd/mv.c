/**
 * @file mv.c
 * @author Mikel Aristu
 *
 * @brief The command used to read files.
 *
 * @version 0.1
 * @date 2021-03-26
 *
 * @copyright Copyright (c) 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>


void _mv()
{

}


int main(int argc, char *argv[])
{
    char *file=argv[1];
    char *subdir=argv[2];
    char newdirec[50];
    
    if (argc<=1 || argc>=3){
        //If the command is used incorrectly, it will teach the user how to use it.
        howToUse();
     }else if(argc==2){
        DIR *direc;
        direc= opendir(subdir);
        char *current;

        current=getcwd(newdirec,50);

     }

}

void howToUse()
{
    printf("Usage:\n mv file.txt subdir\n");
    exit(1);
}