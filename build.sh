#!/bin/bash

# Build the compiler
#
# You MUST replace the following commands with the commands for building your compiler

case "$1" in
-c)
    make clean -C ./src > /dev/null
    ;;
-b)
    make -C ./src > /dev/null
    ;;
"")
    make clean -C ./src > /dev/null
    make -C ./src > /dev/null
    ;;
esac
