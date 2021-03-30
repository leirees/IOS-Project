#!/bin/bash
gcc -fPIC -c signal_handler.c
gcc -shared -Wl,-soname,libsignal.so -o libsignal.so signal_handler.o