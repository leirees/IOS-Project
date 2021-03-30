#!/bin/bash
gcc -fPIC -c libstring.c
gcc -shared -Wl,-soname,libstring.so -o libstring.so libstring.o