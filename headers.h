//Used for basic input/output stream
#include <stdio.h>
#include <stdlib.h>

//Used for handling directory files
#include <dirent.h>

//For EXIT codes and error handling
#include <errno.h>

// String managing
#include "string/string.h"

// Unix syscall managing
#include <unistd.h>
#include <sys/wait.h>

// EXIT codes
#define SUCCESS 0
#define ERROR   1

// COLORS in ANSI, for Terminal coloring
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
