#!/bin/bash

rm part8 s8b 2>/dev/null
gcc part8.c -o part8 2>> s8b
if [[ -s s8b ]]
then
    echo There is a compile warning/error.
fi
if [[ ! -x part8 ]] 
then 
    echo part8 executable cannot be generated
#    echo part 8 mark is 0
    exit
fi
rm s8b 2>/dev/null
./part8 p8b.obj > s8b 2>/dev/null
if [[  -e s8b ]]
then
    ./compareExamples s8b answer8b
fi
rm part8 s8b 2>/dev/null

