/**
 * @file grep.c
 * @author The Wizard of OS team
 * @brief Prints the line containing the word and the occurance number
 * @version 1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/grep.h"

int main(int argc, char *argv[])
{
    int des, fhandle, i, j, k, arg_ind = 2, occurances = 0;
    int linecount;
    int lineflag;
    char buf, line[160];

    // In order to change the format to bold
    char ESC = 27;

    if (argc < 4) // To check the syntax
    {
        error("Error... Correct Syntax is : grep \"pattern\" \"filename\"\n");                                                                        //Exit program
    }

    lineflag = 0;

    // Open the file specified by the command
    des = open(argv[3], O_RDONLY);
    linecount = 0;

    // Read upto the end of file and copy to the array line[i].
    do
    {
        i = 0;
        do //Read a line
        {
            fhandle = read(des, &buf, 1);
            line[i++] = buf;
        } while ((fhandle != 0) && (buf != '\n'));

        line[i] = '\0';
        linecount++;
        i = 0;

        while (line[i] != '\0') //Check character matching
        {
            if (line[i] == argv[2][0])
            {
                k = 1;
                i++;
                while ((k < strlen(argv[2])) && (line[i] == argv[2][k])) //Check all characters in a line
                {
                    i++;
                    k++;
                }

                if (k == strlen(argv[2]))
                {
                    printf("%s", line); // Print out the line
                    occurances++;       // Count occurances of that string
                }
            }

            i++;
        }

    } while (fhandle != 0);

    char *res = "Number of occurances: %d";
    sprintf(res, occurances);
    println(bold(res));
    
    close(des);
    arg_ind++;
}