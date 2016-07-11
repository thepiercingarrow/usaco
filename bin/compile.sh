#!/bin/bash
for EXT in 'c' 'cpp'; do
    for SOURCE in $(find . -type f -name "*.${EXT}"); do
	if [ ! $1 ] || test $1 != '-s' -a $1 != '--silent'; then
            echo gcc $SOURCE -O2 -o $(echo $SOURCE | sed "s/\.${EXT}$/\.out/g")
	fi
	gcc $SOURCE -O2 -o $(echo $SOURCE | sed "s/\.${EXT}$/\.out/g")
    done
done
