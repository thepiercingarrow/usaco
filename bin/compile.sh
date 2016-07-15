#!/bin/bash
if test ! -d build/; then
    mkdir -p build/
fi
for EXT in 'c' 'cpp'; do
    for SOURCE in $(find . -type f -name "*.${EXT}"); do
	mkdir -p $(echo $SOURCE | sed 's/src/build/g' | sed 's/[a-z1-9\.]*$//g')
	if [ ! $1 ] || test $1 != '-s' -a $1 != '--silent'; then
            echo gcc $SOURCE -O2 -o $(echo $SOURCE | sed 's/src/build/g' | sed "s/\.${EXT}$//g") -lm
	fi
	gcc $SOURCE -O2 -o $(echo $SOURCE | sed 's/src/build/g' | sed "s/\.${EXT}$//g") -lm
	if [ $? != 0 ]; then
	    exit 1;
	fi
    done
done
