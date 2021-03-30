#!/bin/bash

# Compile exit command.
cd exit_cmd
./compile_exit.sh
cd ..

# Compile libsignal
cd signals_lib
./compile_signallib.sh

sudo cp libsignal.so /usr/lib
sudo chmod 0755 /usr/lib/libsignal.so

cd ..

# Compile stringlib
cd string_lib
./compile_stringlib.sh

sudo cp libstring.so /usr/lib
sudo chmod 0755 /usr/lib/libstring.so

cd ..

# Configure ldcache
sudo ldconfig

# Compile main program. SHELL.
gcc -o shell shell.c -lstring -lsignal