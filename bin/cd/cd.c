/**
 * @file cd.c
 * @author Team 2.2
 * 
 * @brief The command cd that will let the user move around directories.
 * 
 * @version 0.1
 * @date 2021-03-16
 * 
 * @copyright Copyright (c) 2021
 */

// Utilities to deal with files, directories.
#include "../utilities.h"
#include "../path.h"

void _cd(char *path){
    chdir(path);
}

int main(int argc, const char *argv[]){

    if (argc<=1 || argc>=3){
        //If the command is used incorrectly, it will teach the user how to use it.
        write(2, "Usage: cd directory\n", 19);

    }else if(argc==2){
            //try to open the directory written
             DIR *dh = opendir(argv[1]);

        if(argv[1]==".."){
            //Go back to the previous directory.
           _cd("..");

        }else if(argv[1]=="."){
            //Print the current directory.
            pwd();

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
    return 0;
}