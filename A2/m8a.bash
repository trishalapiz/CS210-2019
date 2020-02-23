#!/bin/bash

rm part8 s8a 2>/dev/null
gcc part8.c -o part8 2>> s8a
if [[ -s s8a ]]
then
    echo There is a compile warning/error.
fi
if [[ ! -x part8 ]] 
then 
    echo part8 executable cannot be generated
#    echo part 8 mark is 0
    exit
fi
rm s8a 2>/dev/null
./part8 p8a.obj > s8a 2>/dev/null
if [[  -e s8a ]]
then
    ./compareExamples s8a answer8a
fi
rm part8 s8a 2>/dev/null

