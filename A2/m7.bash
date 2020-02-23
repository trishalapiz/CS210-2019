#!/bin/bash

rm part7 s7 2>/dev/null
gcc part7.c -o part7 2>> s7
if [[ -s s7 ]]
then
    echo There is a compile warning/error.
fi
if [[ ! -x part7 ]] 
then 
    echo part7 executable cannot be generated
    echo part 7 mark is 0
    exit
fi
rm s7 2>/dev/null
./part7 p7.obj > s7 2>/dev/null
if [[  -e s7 ]]
then
    ./compareExamples s7 answer7
fi
rm part7 s7 2>/dev/null
