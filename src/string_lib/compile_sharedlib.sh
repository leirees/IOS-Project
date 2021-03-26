#!/bin/bash
gcc -fPIC -c string.c
gcc -shared -Wl,-soname,libstring.so -o libstring.so string.o