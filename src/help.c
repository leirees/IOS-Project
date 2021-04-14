//For write system call
#include <unistd.h>
//Used for basic input/output stream
#include <stdio.h>
//Standart library
#include <stdlib.h>
#include <sys/uio.h>
//For string concatenation
#include <string.h>

void _help(){

	write(1, "\ncat :\n", 7);
	write(1, "\tRead a file and write it in the standard output.\n", 50);
	write(1, "\ncd :\n", 6);
	write(1, "\tMove around nearby directories.\n", 33);
	write(1, "\ncp :\n", 6);
	write(1, "\tCopy files and directories.\n", 29);
	write(1, "\nexit :\n", 8);
	write(1, "\tCause normal process termination.\n", 35);
	write(1, "\ngrep :\n", 8);
	write(1, "\tPrint the occurrences of a string in lines and the number of them.\n", 68);
	write(1, "\nhelp :\n", 8);
	write(1, "\tDisplay information about builtin commands.\n", 45);
	write(1, "\nls :\n", 6);
	write(1, "\tList the content of the current directory.\n", 44);
	write(1, "\nmv :\n", 6);
	write(1, "\tMove (remame) files.\n", 22);
	write(1, "\npwd :\n", 7);
	write(1, "\tPrint name of current/working directory.\n", 42);
	write(1, "\nstee :\n", 8);
	write(1, "\tStore a line from stdin in a file.\n", 36);
	write(1, "\ntouch :\n", 9);
	write(1, "\tCreate a new file or change timestamps.\n\n", 42);
}

int main(int argc, const char *argv[]){

	if (argc == 1){		//If there is one argument
		_help();	//call help
	} else if (argc != 1){	//If incorrect number of arguments
		write(2, "\nError... Correct Syntax is: help\n\n", 35);	//To standart error
	}
	return 0;
}