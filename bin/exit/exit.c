#include "../utilities.h"
#include "../colors.h"

int main(int argc, char * argv[])
{
    char *exitmsg = "BYE!!\n";

    // String manipulation to add yellow color.
    char *dest = ANSI_COLOR_YELLOW;
    strcat(dest, exitmsg);
    // strcat(dest, ANSI_COLOR_RESET);

    write(1, dest, strlen(dest));
    // exit(0);
}