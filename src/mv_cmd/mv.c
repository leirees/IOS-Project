/**
 * @file mv.c
 * @author Mikel Aristu
 *
 * @brief The command used to move a file to a different location.
 *
 * @version 0.1
 * @date 2021-03-26
 *
 * @copyright Copyright (c) 2021
 */

#include <mv.h>

void howToUse();

int main(int argc, char *argv[])
{
    char *file=argv[1];
    char *subdir=argv[2];
    char newdirec[50];
    
    if (argc<=2 || argc>=4){
        //If the command is used incorrectly, it will teach the user how to use it.
        howToUse();
     }else if(argc==3){
        DIR *direc;
        direc= opendir(subdir);
        
        if(direc==NULL){
            printf("Error: File not moved\n");
        }else{
            char *current;
            current=getcwd(newdirec,50);

            concat(newdirec,"/");
            concat(newdirec,subdir);
            concat(newdirec,"/");                    // attach mv location to path 
            concat(newdirec, file);                        // keep original file name
            if(rename(file, direc)!=-1)
                printf("Successful\n");
            else
                printf("Error:\nDirectory not found in CWD\n");
        closedir(direc);
        }
     }

}

void howToUse()
{
    printf("Usage:\n mv file.txt new_location\n");
    exit(1);
}