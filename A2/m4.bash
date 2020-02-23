#!/bin/bash

rm part4 s4 2>/dev/null
gcc part4.c -o part4 2>> s4
if [[ -s s4 ]]
then
    echo There is a compile warning/error.
fi
if [[ ! -x part4 ]] 
then 
    echo part4 executable cannot be generated
    echo part 4 mark is 0
    exit
fi
rm s4 2>/dev/null
./part4 p4.obj > s4 2>/dev/null
if [[  -e s4 ]]
then
    ./compareExamples s4 answer4
fi
rm part4 s4 2>/dev/null
