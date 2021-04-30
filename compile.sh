#!/bin/bash
# SCRIPT FOR COMPILING ALL THE DEPENDENCES THE PROGRAM WILL NEED.
# BY DAVID CUENCA MARCOS, 30/03/2021.
# CHANGES...
# MOD. David Cuenca Marcos, 14/04/2021.

echo "Current location: $(pwd)"

# Compile and make libstring work
if [[ -n "$(git diff src/libstring/libstring.c)" || -n "$(git diff src/headers/libstring.h)" ]]; then
    echo "Compile libstring mod."
    gcc -fPIC -c src/libstring/libstring.c -o build/libstring.o
    gcc -shared -Wl,-soname,libstring.so -o build/libstring.so build/libstring.o

    sudo cp build/libstring.so /usr/lib
    sudo chmod 0755 /usr/lib/libstring.so
fi

# Configure ldcache
sudo ldconfig

############### COMMAND COMPILATION PROCESS ###############

# Compile CAT command.
if [[ !(-s bin/cat) || -n "$(git diff src/cat.c)" || -n "$(git diff src/headers/cat.h)" ]]; then
    echo "Compile cat."
    gcc -O2 src/cat.c -o bin/cat -lstring
fi

# Compile CD command.
if [[ -n "$(git diff src/cd.c)" || -n "$(git diff src/headers/cd.h)" ]]; then
    echo "Compile cd."
    gcc -c src/cd.c -o build/cd.o -lstring
fi

# Compile CP command.
if [[ !(-s bin/cp) || -n "$(git diff src/cp.c)" || -n "$(git diff src/headers/cp.h)" ]]; then
    echo "Compile cp."
    gcc -O2 src/cp.c -o bin/cp -lstring
fi

# Compile EXIT command.
if [[ -n "$(git diff src/exit.c)" || -n "$(git diff src/headers/exit.h)" ]]; then
    echo "Compile exit."
    gcc -c src/exit.c -o build/exit.o -lstring
fi

# Compile GREP command.
if [[ !(-s bin/grep) || -n "$(git diff src/grep.c)" || -n "$(git diff src/headers/grep.h)" ]]; then
    echo "Compile grep."
    gcc -O2 src/grep.c -o bin/grep -lstring
fi

# Compile HELP command.
if [[ !(-s bin/help) || -n "$(git diff src/help.c)" || -n "$(git diff src/headers/help.h)" ]]; then
    echo "Compile help."
    gcc -O2 src/help.c -o bin/help -lstring
fi

# Compile LS command.
if [[ !(-s bin/ls) || -n "$(git diff src/ls.c)" || -n "$(git diff src/headers/ls.h)" ]]; then
    echo "Compile ls."
    gcc -O2 src/ls.c -o bin/ls -lstring
fi

# Compile MV command.
if [[ !(-s bin/mv) || -n "$(git diff src/mv.c)" || -n "$(git diff src/headers/mv.h)" ]]; then
    echo "Compile mv."
    gcc -O2 src/mv.c -o bin/mv -lstring
fi

# Compile PWD command.
if [[ !(-s bin/pwd) || -n "$(git diff src/pwd.c)" || -n "$(git diff src/headers/pwd.h)" ]]; then
    echo "Compile pwd."
    gcc -O2 src/pwd.c -o bin/pwd -lstring
fi

# Compile STEE command.
if [[ !(-s bin/stee) || -n "$(git diff src/stee.c)" || -n "$(git diff src/headers/stee.h)" ]]; then
    echo "Compile stee."
    gcc -O2 src/stee.c -o bin/stee -lstring
fi

# Compile TOUCH command.
if [[ !(-s bin/touch) || -n "$(git diff src/touch.c)" || -n "$(git diff src/headers/touch.h)" ]]; then
    echo "Compile touch."
    gcc -O2 src/touch.c -o bin/touch -lstring
fi

# Compile MAN command.
if [[ !(-s bin/man) || -n "$(git diff src/man.c)" || -n "$(git diff src/headers/man.h)" ]]; then
    echo "Compile man."
    gcc -O2 src/man.c -o bin/man -lstring
fi

############### COMMAND COMPILATION PROCESS ###############

# COMPILE SHELL.
if [[ !(-s shell) || -n "$(git diff src/shell.c)" || -n "$(git diff src/headers/shell.h)" ]]; then
    echo "COMPILING GAME FILE"
    gcc src/shell.c src/cd.c src/exit.c src/signal_handler.c src/menu.c src/char*.c -o TheWizardOfOS -lstring
fi

echo "**END**"