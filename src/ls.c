/**
 * @file ls.c
 * @author Zdravko Todorov, Team 2.2
 * @brief Lists the directory and files.
 * @version 1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */
#include "headers/ls.h"

void _ls(const char *dir, int op_a, int op_l)
{
	char *err_title = THE_SYSTEM;

	// Pointer to stat struct
	struct stat sfile;

	// Here we will list the directory
	struct dirent *d;

	/* 1- Try to open the directory */
	DIR *dh = opendir(dir);

	//If the directory is not accessible
	if (!dh)
	{
		// Throw error and exit
		if (errno = ENOENT)
		{
			// If the directory is not found
			printerr("Directory doesn't exist. Try again, ape.", err_title);
		}
		else
		{
			// If the directory is not readable
			printerr("Unable to read directory. Try again, ape.", err_title);
		}

		free(err_title);
		_exit(EXIT_FAILURE);
	}

	/* 2- While the next entry is not readable we will print directory files */
	d = readdir(dh);

	while (d != NULL)
	{
		// If hidden files are found we continue
		// if (!op_a && d->d_name[0] == '.')
		// 	continue;

		// if (!op_a)
		// {
		// 	// char yellow[7 + strlen(d->d_name) + 4], name[strlen(d->d_name)], defaultcol[5]; 	//Allocate
		// 	// strcpy(yellow, "\033[0;33m");													//Store yellow color
		// 	// strcpy(name, d->d_name);															//Store name
		// 	// strcpy(defaultcol, "\033[0m");													//Store default color
		// 	// strcat(yellow, name);															//Concatenate color code + name
		// 	// strcat(yellow, defaultcol);														//Add default color code to string
		// 	// write(1, yellow, strlen(yellow));

		// 	// Write the name in yellow
		// 	println(concat(ANSI_COLOR_YELLOW, d->d_name));
		// }
		// else if (op_a && d->d_name[0] == '.')
		// {
		// 	//hemen idatzi urdinez
		// }

		/* -a option */
		// Simplified version of the code above.
		if (d->d_name[0] == '.')
		{
			if (op_a)
			{
				// Show the alternative path, if requested.
				println(concat(ANSI_COLOR_CYAN, d->d_name));
			}
			else
			{
				// Else, leave it hidden, in the night of the Terminal.
				continue;
			}
		}
		else
		{
			// For the main path, simply print it on screen.
			println(concat(ANSI_COLOR_YELLOW, d->d_name));
		}

		// if (!op_l)
		// 	write(1, "\n", 2); //New line if not -l

		// if (op_l) //If -l
		// {
		// 	//stat system call
		// 	stat(d->d_name, &sfile);
		// 	//Accessing st_size (of stat struct) --> Size
		// 	printf("\n  Size: %ld", sfile.st_size);
		// 	//Accessing st_uid (of stat struct) --> User ID
		// 	printf("\n  User ID: %d", sfile.st_uid);
		// 	//Accessing st_mode (of stat struct) --> Permissions
		// 	printf("\n  File Permissions User: ");
		// 	printf((sfile.st_mode & S_IRUSR) ? "r" : "-");
		// 	printf((sfile.st_mode & S_IWUSR) ? "w" : "-");
		// 	printf((sfile.st_mode & S_IXUSR) ? "x" : "-");
		// 	printf("\n");
		// }

		// if (!op_l)
		// {
		// 	printf("\n");
		// }

		/* -l option */
		// Simplified version of the code above.
		if (op_l)
		{
			// Stat syscall, in order to get additional info about a file.
			stat(d->d_name, &sfile);

			/* Properties of the file */
			// Accessing st_size --> Size.
			char *size;
			sprintf(size, "Size: %ld", sfile.st_size);
			println(size);
			// Accessing st_uid  --> User ID.
			char *uid;
			sprintf(uid, "User ID: %d", sfile.st_uid);
			println(uid);
			// Accessing st_mode --> Permissions.
			println("User file permissions: ");
			print("\t");
			print((sfile.st_mode & S_IRUSR) ? "r" : "-");
			print((sfile.st_mode & S_IWUSR) ? "w" : "-");
			print((sfile.st_mode & S_IXUSR) ? "x" : "-");
			print("\n");
		}
		else
		{
			println("");
		}

		d = readdir(dh);
	}
}

int main(int argc, const char *argv[])
{
	char *err_title = THE_SYSTEM;

	if (argc == 1)
	{
		// If there is one argument, call ls alone, to ".".
		_ls(".", 0, 0);
	}
	else if (argc == 2)
	{
		// If there are two arguments, check if a valid option is passed:
		if (argv[1][0] == '-')
		{
			// Supported options: -a, -l
			int op_a = 0;
			int op_l = 0;

			// Read the option
			char *p = (char *)(argv[1] + 1);

			while (*p)
			{
				if (*p == 'a')
				{
					// If option is a
					op_a = 1;
				}
				else if (*p == 'l')
				{
					// If option is l
					op_l = 1;
				}
				else
				{
					printerr("Option not available. Try again, you useless ape.", err_title);
					_exit(EXIT_FAILURE);
				}

				p++;
			}

			// Call ls
			_ls(".", op_a, op_l);
		}
	}

	free(err_title);
	_exit(EXIT_SUCCESS);
}