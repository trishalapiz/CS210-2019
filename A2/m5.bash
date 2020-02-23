#!/bin/bash

rm part5 s5 2>/dev/null
gcc part5.c -o part5 2>> s5
if [[ -s s5 ]]
then
    echo There is a compile warning/error.
fi
if [[ ! -x part5 ]] 
then 
    echo part5 executable cannot be generated
    echo part 5 mark is 0
    exit
fi
rm s5 2>/dev/null
./part5 p5.obj > s5 2>/dev/null
if [[  -e s5 ]]
then
    ./compareExamples s5 answer5
fi
rm part5 s5 2>/dev/null
