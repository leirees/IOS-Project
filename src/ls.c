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
#include "headers/characters/character.h"

void _ls(const char *dir, int op_a, int op_l)
{
	char *err_title = THE_SYSTEM;

	// Pointer to stat struct
	struct stat sfile;
	char *size = (char *)malloc(strlen("Size: %ld") + sizeof(sfile.st_size));
	char *uid = (char *)malloc(strlen("User ID: %d") + sizeof(sfile.st_uid));

	// Here we will list the directory
	struct dirent *d;

	/* 1- Try to open the directory */
	DIR *dh = opendir(dir);

	//If the directory is not accessible
	if (dh == NULL)
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

		printerr("ERROR!", err_title);
		_exit(EXIT_FAILURE);
	}

	/* 2- While the next entry is not readable we will print directory files */
	while ((d = readdir(dh)) != NULL)
	{
		if (d->d_name[0] == '.')
		{
			if (op_a)
			{
				// Show the alternative path, if requested.
				println(concat(ANSI_COLOR_CYAN, d->d_name));
			}
			else
			{
				continue;
			}
		}
		else
		{
			if (!strcmp(d->d_name, "emerald_city"))
			{
				// If we are in Emerald City, print in Green color and bold (Emerald City)
				println(concat(concat(BOLD, concat(ANSI_COLOR_GREEN, d->d_name)), NO_BOLD));
			}
			else
			{
				// For the main path, simply print it on screen.
				println(concat(ANSI_COLOR_YELLOW, d->d_name));
			}
		}

		// If ls -l,
		if (op_l)
		{
			// Stat syscall, in order to get additional info about a file.
			stat(d->d_name, &sfile);

			//Accessing st_size (of stat struct) --> Size
			// printf("Size: %ld", sfile.st_size);
			// //Accessing st_uid (of stat struct) --> User ID
			// printf("\n  User ID: %d", sfile.st_uid);
			// //Accessing st_mode (of stat struct) --> Permissions
			// printf("\n  File Permissions User: ");
			// printf((sfile.st_mode & S_IRUSR) ? "r" : "-");
			// printf((sfile.st_mode & S_IWUSR) ? "w" : "-");
			// printf((sfile.st_mode & S_IXUSR) ? "x" : "-");
			// printf("\n");

			/* Properties of the file */
			// Accessing st_size --> Size.
			sprintf(size, "Size: %ld", sfile.st_size);
			println(size);
			// Accessing st_uid  --> User ID.
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
	}

	free(err_title);
	free(size);
	free(uid);
}

int main(int argc, const char *argv[])
{
	char *err_title = THE_SYSTEM;

	if (argc == 1)
	{
		// If there is one argument, call ls alone, to ".".
		_ls(".", 0, 0);
	}
	else if (argc <= 3)
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
					// If option is -a
					op_a = 1;
				}
				else if (*p == 'l')
				{
					// If option is -l
					op_l = 1;
				}
				else
				{
					printerr("Option not available. Try again, you useless ape.", err_title);
					_exit(EXIT_FAILURE);
				}

				p++;
			}

			if (argc == 3)
			{
				_ls(argv[2], op_a, op_l);
			}
			else if (argc == 2)
			{
				_ls(".", op_a, op_l);
			}
			else
			{
				printerr("Option not available. Try again, you useless ape.", err_title);
				_exit(EXIT_FAILURE);
			}
		}
		else if (argc == 2)
		{
			_ls(argv[1], 0, 0);
		}
		else
		{
			printerr("Option not available. Try again, you useless ape.", err_title);
			_exit(EXIT_FAILURE);
		}
	}

	free(err_title);
	_exit(EXIT_SUCCESS);
}