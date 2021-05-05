#include "headers/main_header.h"
#include "headers/libstring/libstring.h"

void clear_screen()
{
    for (u16 rows = 0; rows < MAXLINE; rows++)
    {
        println("");
    }
}

int main()
{
    clear_screen();
    _exit(0);
}