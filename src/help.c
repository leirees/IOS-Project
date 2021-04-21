/**
 * @file help.c
 * @author The Wizard of OS team
 * @brief Gives info about available commands
 * @version 1
 * @date 2021-04-21
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/help.h"

void _help(){

	write(1, "\nThis is what you can use:\n", 27);
	//Prints all the available commands to the stdout
	write(1, "\nhelp :\n", 8);
	write(1, "\tYou've just used it.\n", 22);
	write(1, "\ncat :\n", 7);
	write(1, "\tRead a note you have found.\n", 29);
	write(1, "\ncd :\n", 6);
	write(1, "\tGo to a new location.\n", 23);
	write(1, "\ncp :\n", 6);
	write(1, "\tClone something.\n", 18);
	write(1, "\ngrep :\n", 8);
	write(1, "\tSearch a word in a book.\n", 26);
	write(1, "\nls :\n", 6);
	write(1, "\tLook around you.\n", 18);
	write(1, "\nmv :\n", 6);
	write(1, "\tMove items from one place to another.\n", 39);
	write(1, "\npwd :\n", 7);
	write(1, "\tLocate yourself in the Terminal World.\n", 40);
	write(1, "\nstee :\n", 8);
	write(1, "\tEdit a file.\n", 14);
	write(1, "\ntouch :\n", 9);
	write(1, "\tCraft a new item.\n", 19);
	write(1, "\nexit :\n", 8);
	write(1, "\tTo exit the Terminal World.\n\n", 30);
}

int main(int argc, const char *argv[]){

	if (argc == 1){		//If there is one argument
		_help();	//call help
	} else if (argc != 1){	//If incorrect number of arguments
		write(2, "\nYou can't even write a word correctly...\n", 42);	//To standart error
		speak_ofelia("Look at the manual, you little useless piece of garbage!", 0);		//Bad witch in action
	}
	return 0;
}