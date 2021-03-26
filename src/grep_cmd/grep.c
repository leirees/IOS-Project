#include <string.h>
#include <fcntl.h>  //Defines flags for open and related library functions
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int des, fhandle, i, j, k, arg_ind = 2, occurances = 0;
    int linecount;
    int lineflag;
    char buf, line[160];

    if (argc < 4) // To check the syntax
    {
        printf("\n Error... Correct Syntax is : grep \"pattern\" \"filename\"\n");
        exit(0);
    }

    lineflag = 0;
    des = open(argv[3], O_RDONLY); //Open the file specified by the command
    linecount = 0;

    do //Read upto the end of file and copy to the array line[].
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
                while ((k < strlen(argv[2])) && (line[i] == argv[2][k]))    //Check all characters in a line
                {
                    i++;
                    k++;
                }
                if (k == strlen(argv[2])){      
                    printf("%s", line);         //Print out the line
                    occurances++;               //Count occurances of that string
                } 
            }
            i++;
        }
    } while (fhandle != 0);
    
    printf("\n  Number of occurances: %d \n", occurances);
    close(des);
    arg_ind++;
    printf("\n");
}