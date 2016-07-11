#!/bin/bash
for PROG in $(find . -type f -name "*.out" | sed 's/^\.\/src\///g' | sed 's/\.out$//g'); do
    echo $PROG
done
