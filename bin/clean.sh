#!/bin/bash
for PROG in $(find . -type f -regex '.*\.cp*' | sed 's/\.cp*//g'); do
    echo Removing: $PROG
    rm -f $PROG
done
find . -type f -name '*.in'
find . -type f -name '*.out'
