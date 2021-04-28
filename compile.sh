#!/bin/bash
#!/bin/zsh

# SCRIPT FOR COMPILING ALL THE DEPENDENCES THE PROGRAM WILL NEED.
# CREATION
# BY DAVID CUENCA MARCOS, 30/03/2021.
# CHANGESLOG
# MOD. David Cuenca Marcos, 14/04/2021.
# MOD. David Cuenca Marcos, 28/04/2021: ALL flag, for complete compilation; .version saving, for later, next compilations,
# in other Linux flavours, Windows.

# true iff Compile everything, as an argument.
ALL="$1"

last_vers="$(uname -r)"
vers=$last_vers

if [[ !(-s .version) ]]; then
    echo $vers > .version
else
    last_vers="$(cat .version)"

    if [[ $vers != $last_vers ]]; then
        echo "Different OS than before. Recompiling."
        echo "Last time: $last_vers"
    fi
fi

echo "Current OS: $vers"
echo "Current location: $(pwd)"

# Compile and make libstring work
if [[ $ALL == "true" || $last_vers != $vers || -n "$(git diff src/libstring/libstring.c)" || -n "$(git diff src/headers/libstring.h)" ]]; then
    echo "Compile libstring mod."
    gcc -fPIC -c src/libstring/libstring.c -o build/libstring.o
    gcc -shared -Wl,-soname,libstring.so -o build/libstring.so build/libstring.o

    chmod 0755 build/libstring.so
fi

libstring="build/libstring.so"

############### COMMAND COMPILATION PROCESS ###############

# Compile CAT command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/cat) || -n "$(git diff src/cat.c)" || -n "$(git diff src/headers/cat.h)" ]]; then
    echo "Compile cat."
    gcc -O2 src/cat.c -o bin/cat -L$libstring -lstring
fi

# Compile CD command.
if [[ $ALL == "true" || $last_vers != $vers || -n "$(git diff src/cd.c)" || -n "$(git diff src/headers/cd.h)" ]]; then
    echo "Compile cd."
    gcc -c src/cd.c -o build/cd.o -L$libstring -lstring
fi

# Compile CP command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/cp) || -n "$(git diff src/cp.c)" || -n "$(git diff src/headers/cp.h)" ]]; then
    echo "Compile cp."
    gcc -O2 src/cp.c -o bin/cp -L$libstring -lstring
fi

# Compile EXIT command.
if [[ $ALL == "true" || $last_vers != $vers || -n "$(git diff src/exit.c)" || -n "$(git diff src/headers/exit.h)" ]]; then
    echo "Compile exit."
    gcc -c src/exit.c -o build/exit.o -L$libstring -lstring
fi

# Compile GREP command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/grep) || -n "$(git diff src/grep.c)" || -n "$(git diff src/headers/grep.h)" ]]; then
    echo "Compile grep."
    gcc -O2 src/grep.c -o bin/grep -L$libstring -lstring
fi

# Compile HELP command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/help) || -n "$(git diff src/help.c)" || -n "$(git diff src/headers/help.h)" ]]; then
    echo "Compile help."
    gcc -O2 src/help.c -o bin/help -L$libstring -lstring
fi

# Compile LS command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/ls) || -n "$(git diff src/ls.c)" || -n "$(git diff src/headers/ls.h)" ]]; then
    echo "Compile ls."
    gcc -O2 src/ls.c -o bin/ls -L$libstring -lstring
fi

# Compile MV command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/mv) || -n "$(git diff src/mv.c)" || -n "$(git diff src/headers/mv.h)" ]]; then
    echo "Compile mv."
    gcc -O2 src/mv.c -o bin/mv -L$libstring -lstring
fi

# Compile PWD command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/pwd) || -n "$(git diff src/pwd.c)" || -n "$(git diff src/headers/pwd.h)" ]]; then
    echo "Compile pwd."
    gcc -O2 src/pwd.c -o bin/pwd -L$libstring -lstring
fi

# Compile STEE command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/stee) || -n "$(git diff src/stee.c)" || -n "$(git diff src/headers/stee.h)" ]]; then
    echo "Compile stee."
    gcc -O2 src/stee.c -o bin/stee -L$libstring -lstring
fi

# Compile TOUCH command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/touch) || -n "$(git diff src/touch.c)" || -n "$(git diff src/headers/touch.h)" ]]; then
    echo "Compile touch."
    gcc -O2 src/touch.c -o bin/touch -L$libstring -lstring
fi

# Compile MAN command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/man) || -n "$(git diff src/man.c)" || -n "$(git diff src/headers/man.h)" ]]; then
    echo "Compile man."
    gcc -O2 src/man.c -o bin/man -L$libstring -lstring
fi

############### COMMAND COMPILATION PROCESS ###############

# COMPILE SHELL.
if [[ $ALL == "true" || $last_vers != $vers || !(-s shell) || -n "$(git diff src/shell.c)" || -n "$(git diff src/headers/shell.h)" ]]; then
    echo "COMPILING GAME FILE"
    gcc src/shell.c src/cd.c src/exit.c src/signal_handler.c src/menu.c src/character_with_title.c -o TheWizardOfOS -L$libstring -lstring
fi

if [[ $last_vers != $vers ]]; then
    echo $vers > .version
fi

echo "**END of Compilation**"
