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

    //pointer to stat struct
    struct stat sfile;
	//Here we will list the directory
	struct dirent *d;
	DIR *dh = opendir(dir);
	if (!dh){
		if (errno = ENOENT){
			//If the directory is not found
			perror("Directory doesn't exist");
		}
		else{
			//If the directory is not readable then throw error and exit
			perror("Unable to read directory");
		}
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

		if(op_l) {  //If -l
            //stat system call
            stat(d->d_name, &sfile);
            //accessing st_size (of stat struct)   
            printf("\n  Size: %ld", sfile.st_size);
            //accessing st_uid (of stat struct)  
            printf("\n  User ID: %d", sfile.st_uid);
            //accessing st_mode (of stat struct)  
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
	if (argc == 1){
		_ls(".", 0, 0);
	} else if (argc == 2){
		if (argv[1][0] == '-'){
			//Checking if option is passed
			//Options supporting: a, l
			int op_a = 0, op_l = 0;
			char *p = (char*)(argv[1] + 1);
			while(*p){
				if(*p == 'a') op_a = 1;
				else if(*p == 'l') op_l = 1;
				else{
					perror("Option not available");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			_ls(".",op_a,op_l);
		}
	}
	return 0;
}