#!/bin/bash
# SCRIPT FOR COMPILING ALL THE DEPENDENCES THE PROGRAM WILL NEED.
# BY DAVID CUENCA MARCOS, 30/03/2021.

# DEBUG
set -x

# Compile and make libstring work
if [[ -n "$(git diff --cached src/libstring/libstring.c)" && -n "$(git diff --cached src/headers/libstring.h)" ]]; then
    gcc -fPIC -c src/libstring/libstring.c -o build/libstring.o
    gcc -shared -Wl,-soname,libstring.so -o build/libstring.so build/libstring.o

    sudo cp build/libstring.so /usr/lib
    sudo chmod 0755 /usr/lib/libstring.so
fi

# Compile and make libsignals work
if [[ -n "$(git diff --cached src/libsignals/libsignals.c)" && -n "$(git diff --cached src/headers/libsignals.h)" ]]; then
    gcc -fPIC -c src/libsignals/libsignals.c -o build/libsignals.o
    gcc -shared -Wl,-soname,libsignals.so -o build/libsignals.so build/libsignals.o

    sudo cp build/libsignals.so /usr/lib
    sudo chmod 0755 /usr/lib/libsignals.so
fi

# Configure ldcache
sudo ldconfig

############### COMMAND COMPILATION PROCESS ###############

# Compile CAT command.
if [[ -n "$(git diff --cached src/cat.c)" && -n "$(git diff --cached src/headers/cat.h)" ]]; then
    gcc -O2 src/cat.c -o bin/cat
fi

# Compile CD command.
if [[ -n "$(git diff --cached src/cd.c)" && -n "$(git diff --cached src/headers/cd.h)" ]]; then
    gcc -O2 src/cd.c -o bin/cd
fi

# Compile CP command.
if [[ -n "$(git diff --cached src/cp.c)" && -n "$(git diff --cached src/headers/cp.h)" ]]; then
    gcc -O2 src/cp.c -o bin/cp
fi

# Compile EXIT command.
if [[ -n "$(git diff --cached src/exit.c)" && -n "$(git diff --cached src/headers/exit.h)" ]]; then
    gcc -O2 src/exit.c -o bin/exit -lstring
fi

# Compile GREP command.
if [[ -n "$(git diff --cached src/grep.c)" && -n "$(git diff --cached src/headers/grep.h)" ]]; then
    gcc -O2 src/grep.c -o bin/grep
fi

# Compile HELP command.
if [[ -n "$(git diff --cached src/help.c)" && -n "$(git diff --cached src/headers/help.h)" ]]; then
    gcc -O2 src/help.c -o bin/help
fi

# Compile LS command.
if [[ -n "$(git diff --cached src/ls.c)" && -n "$(git diff --cached src/headers/ls.h)" ]]; then
    gcc -O2 src/ls.c -o bin/ls
fi

# Compile MV command.
if [[ -n "$(git diff --cached src/mv.c)" && -n "$(git diff --cached src/headers/mv.h)" ]]; then
    gcc -O2 src/mv.c -o bin/mv
fi

# Compile PWD command.
if [[ -n "$(git diff --cached src/pwd.c)" && -n "$(git diff --cached src/headers/pwd.h)" ]]; then
    gcc -O2 src/pwd.c -o bin/pwd
fi

# Compile STEE command.
if [[ -n "$(git diff --cached src/stee.c)" && -n "$(git diff --cached src/headers/stee.h)" ]]; then
    gcc -O2 src/stee.c -o bin/stee
fi

# Compile TOUCH command.
if [[ -n "$(git diff --cached src/touch.c)" && -n "$(git diff --cached src/headers/touch.h)" ]]; then
    gcc -O2 src/touch.c -o bin/touch
fi

############### COMMAND COMPILATION PROCESS ###############

# COMPILE SHELL.
gcc src/shell.c -o shell -lstring -lsignal