#!/bin/bash
gcc -fPIC -c libsignals.c
gcc -shared -Wl,-soname,libsignals.so -o libsignals.so libsignals.o