// Utilities to deal with files, directories.
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <direct.h>

void _cd(char *path){
    chdir(path);
    write(1, "changed", strlen("changed"));
    printf("\n");
int main(int argc, const char *argv[]){

    if (argc<=1 || argc>=3){
        //If the command is used incorrectly, it will teach the user how to use it.
        write(2, "Usage: cd directory\n", 19);
        printf("\n");
    }else if(argc==2){
            //try to open the directory written
             DIR *dh = opendir(argv[1]);

        if(argv[1]==".."){
            //Go back to the previous directory.
           _cd("..");

        }else if(argv[1]=="."){
            //Print the current directory.
           write(2, "asd",3);

        }else if (!dh){
                    if (errno = ENOENT){
                            //If the directory is not found.
                            perror("Directory doesn't exist");
                    }
                    else{
                            //If the directory is not readable then throw error and exit.
                            perror("Unable to read directory");
                }
                    exit(EXIT_FAILURE);
            }else{
            //Go on to the written directory.
            _cd(readdir(dh)->d_name);
        }
    }
}