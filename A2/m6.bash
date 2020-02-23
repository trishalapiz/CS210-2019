#!/bin/bash

rm part6 s6 2>/dev/null
gcc part6.c -o part6 2>> s6
if [[ -s s6 ]]
then
    echo There is a compile warning/error.
fi
if [[ ! -x part6 ]] 
then 
    echo part6 executable cannot be generated
    echo part 6 mark is 0
    exit
fi
rm s6 2>/dev/null
./part6 p6.obj > s6 2>/dev/null
if [[  -e s6 ]]
then
    ./compareExamples s6 answer6
fi
rm part6 s6 2>/dev/null
