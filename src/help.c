/**
 * @file help.c
 * @author ...
 * @brief ...
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/help.h"

void _help(const char *command, int op_d, int op_m, int op_s) {	
	if (!strcmp(command, "ls"))
	{
		if (op_d)
		{
			/* code */
		}
		if (op_m)
		{
			/* code */
		}
		if (op_s)
		{
			/* code */
		}
	}
	else if (!strcmp(command, "cat"))
	{
		/* code */
	}
}

int main(int argc, const char *argv[]) {
	if (argc == 1)
	{	
		// If there is one argument
		write(2, "\n Error... Correct Syntax is : help [dms] [pattern ...]\n\n", 57);	//To standard error
	} 
	else if (argc == 2){	
		// If there are two arguments
		if (argv[1][0] == '-')
		{
			// Checking if option is passed
			// Options supporting: d, m, s
			int op_d = 0, op_m = 0, op_s = 0;
			char *p = (char*) (argv[1] + 1);	//Read the option
			
			while(*p)
			{
				if(*p == 'd') op_d = 1;	//If option is d
				else if(*p == 'm') op_m = 1;	//If option is m
                else if(*p == 's') op_s = 1;    //If option is s
				else
				{
					perror("Option not available");
					exit(EXIT_FAILURE);
				}
				
				p++;
			}
			
			_help(argv[2], op_d, op_m, op_s);	//call help
		}
	}

	return 0;
}