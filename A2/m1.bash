#!/bin/bash

rm part1 s1 2>/dev/null
gcc part1.c -o part1 2>> s1
if [[ -s s1 ]]
then
    echo There is a compile warning/error.
fi
if [[ ! -x part1 ]] 
then 
    echo part1 executable cannot be generated
    exit
fi
rm s1 2>/dev/null
./part1 p1.obj > s1 2>/dev/null
if [[  -e s1 ]]
then
    ./compareExamples s1 answer1
fi
rm part1 s1 2>/dev/null
