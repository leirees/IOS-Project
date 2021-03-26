#include "exit.h"

int main(int argc, char *argv[])
{
    print("Do you really want to exit the game? \n");
    print(concat(ANSI_COLOR_RED, "OK, good for me!\n"));
    print(concat(ANSI_COLOR_YELLOW, "BYE!!\n"));
    exit(0);
}