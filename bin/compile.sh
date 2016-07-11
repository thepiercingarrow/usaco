#!/bin/bash
for EXT in 'c' 'cpp'; do
    for SOURCE in $(find . -type f -name "*.${EXT}"); do
	echo gcc $SOURCE -O2 -o $(echo $SOURCE | sed "s/\.${EXT}/\.out/g")
	gcc $SOURCE -O2 -o $(echo $SOURCE | sed "s/\.${EXT}/\.out/g")
    done
done
