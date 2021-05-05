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

echo "Current OS: $vers"
echo "Current location: $(pwd)"

if [[ !(-s .version) ]]; then
    echo $vers > .version
else
    last_vers="$(cat .version)"

    if [[ $vers != $last_vers ]]; then
        echo "Different OS than before. Recompiling."
        echo "Last time: $last_vers"
    fi
fi

# Compile libstring
if [[ $ALL == "true" || $last_vers != $vers || -n "$(git diff src/headers/libstring/libstring.c)" || -n "$(git diff src/headers/libstring/libstring.h)" ]]; then
    echo "Compile libstring."
    gcc -c -fpic src/headers/libstring/libstring.c -o build/libstring.o
    gcc -shared build/libstring.o -o build/libstring.so 
    sudo cp build/libstring.so /usr/lib
    sudo chmod 0755 /usr/lib/libstring.so
fi

sudo ldconfig

############### COMMAND COMPILATION PROCESS ###############
echo "Precompiling characters..."
gcc -c src/headers/characters/character.c -o build/characters.o

# Compile CAT command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/cat) || -n "$(git diff src/cat.c)" || -n "$(git diff src/headers/cat.h)" ]]; then
    echo "Compile cat."
    gcc src/cat.c build/characters.o -o bin/cat -lstring
fi

# Compile CP command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/cp) || -n "$(git diff src/cp.c)" || -n "$(git diff src/headers/cp.h)" ]]; then
    echo "Compile cp."
    gcc src/cp.c -o bin/cp -lstring
fi

# Compile GREP command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/grep) || -n "$(git diff src/grep.c)" || -n "$(git diff src/headers/grep.h)" ]]; then
    echo "Compile grep."
    gcc src/grep.c -o bin/grep -lstring
fi

# Compile HELP command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/help) || -n "$(git diff src/help.c)" || -n "$(git diff src/headers/help.h)" ]]; then
    echo "Compile help."
    gcc src/help.c build/characters.o -o bin/help -lstring
fi

# Compile LS command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/ls) || -n "$(git diff src/ls.c)" || -n "$(git diff src/headers/ls.h)" ]]; then
    echo "Compile ls."
    gcc src/ls.c build/characters.o -o bin/ls -lstring
fi

# Compile MV command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/mv) || -n "$(git diff src/mv.c)" || -n "$(git diff src/headers/mv.h)" ]]; then
    echo "Compile mv."
    gcc src/mv.c build/characters.o -o bin/mv -lstring
fi

# Compile PWD command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/pwd) || -n "$(git diff src/pwd.c)" || -n "$(git diff src/headers/pwd.h)" ]]; then
    echo "Compile pwd."
    gcc src/pwd.c build/characters.o -o bin/pwd -lstring
fi

# Compile STEE command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/stee) || -n "$(git diff src/stee.c)" || -n "$(git diff src/headers/stee.h)" ]]; then
    echo "Compile stee."
    gcc src/stee.c build/characters.o -o bin/stee -lstring
fi

# Compile TOUCH command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/touch) || -n "$(git diff src/touch.c)" || -n "$(git diff src/headers/touch.h)" ]]; then
    echo "Compile touch."
    gcc src/touch.c build/characters.o -o bin/touch -lstring
fi

# Compile MAN command.
if [[ $ALL == "true" || $last_vers != $vers || !(-s bin/man) || -n "$(git diff src/man.c)" || -n "$(git diff src/headers/man.h)" ]]; then
    echo "Compile man."
    gcc src/man.c build/characters.o -o bin/man -lstring
fi

############### COMMAND COMPILATION PROCESS ###############

# COMPILE SHELL.
if [[ $ALL == "true" || $last_vers != $vers || !(-s shell) || -n "$(git diff src/shell.c)" || -n "$(git diff src/headers/shell.h)" ]]; then
    echo "COMPILING GAME FILE"
    gcc -c src/cd.c -o build/cd.o
    gcc -c src/exit.c -o build/exit.o
    gcc -c src/signal_handler.c -o build/signal_handler.o
    gcc -c src/menu.c -o build/menu.o
    
    gcc src/shell.c build/cd.o build/exit.o build/signal_handler.o build/menu.o build/characters.o -o TheWizardOfOS -lstring
fi

if [[ $last_vers != $vers ]]; then
    echo $vers > .version
fi

echo "**END of Compilation**"
