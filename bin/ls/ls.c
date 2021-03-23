//Used for basic input/output stream
#include <stdio.h>
//Used for handling directory files
#include <dirent.h>
//For EXIT codes and error handling
#include <errno.h>
#include <stdlib.h>
//For stat system call for file attributes
#include <sys/stat.h>
//For write system call
#include <unistd.h>
//For string concatenation
#include <string.h>

void _ls(const char *dir,int op_a,int op_l){
	
    //Pointer to stat struct
    struct stat sfile;
	//Here we will list the directory
	struct dirent *d;
	DIR *dh = opendir(dir);
	//If the directory is not accessible
	if (!dh){
		if (errno = ENOENT){
			//If the directory is not found
			perror("Directory doesn't exist");
		}
		else{
			//If the directory is not readable
			perror("Unable to read directory");
		}
		//Throw error and exit
		exit(EXIT_FAILURE);
	}

	//While the next entry is not readable we will print directory files
	while ((d = readdir(dh)) != NULL){
		//If hidden files are found we continue
		if (!op_a && d->d_name[0] == '.') continue;
        
        char yellow[7 + strlen(d->d_name) + 4], name[strlen(d->d_name)], defaultcol[5]; //Allocate
        strcpy(yellow, "\033[0;33m");   //Store yellow color
        strcpy(name, d->d_name);    //Store name
        strcpy(defaultcol, "\033[0m");  //Store default color
        strcat(yellow, name);   //Concatenate color code + name
        strcat(yellow, defaultcol); //Add default color code to string
        write(1, yellow, strlen(yellow));   //Write the name in yellow
		if (!op_l) write(1, "\n", 2);	//New line if not -l

		if(op_l) {  //If -l
            //stat system call
            stat(d->d_name, &sfile);
            //Accessing st_size (of stat struct) --> Size 
			printf("\n  Size: %ld", sfile.st_size);
            //Accessing st_uid (of stat struct) --> User ID
            printf("\n  User ID: %d", sfile.st_uid);
            //Accessing st_mode (of stat struct) --> Permissions
            printf("\n  File Permissions User: ");
            printf((sfile.st_mode & S_IRUSR)? "r":"-");
            printf((sfile.st_mode & S_IWUSR)? "w":"-");
            printf((sfile.st_mode & S_IXUSR)? "x":"-");
			printf("\n");
		}
	}

	if(!op_l) {
		printf("\n");
	}
}

int main(int argc, const char *argv[]){
	if (argc == 1){		//If there is one argument
		_ls(".", 0, 0);		//call ls
	} else if (argc == 2){	//If there are two arguments
		if (argv[1][0] == '-'){
			//Checking if option is passed
			//Options supporting: a, l
			int op_a = 0, op_l = 0;
			char *p = (char*)(argv[1] + 1);	//Read the option
			while(*p){
				if(*p == 'a') op_a = 1;	//If option is a
				else if(*p == 'l') op_l = 1;	//If option is l
				else{
					perror("Option not available");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			_ls(".",op_a,op_l);	//call ls
		}
	}
	return 0;
}