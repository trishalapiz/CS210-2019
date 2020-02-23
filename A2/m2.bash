#!/bin/bash

rm part2 s2 2>/dev/null
gcc part2.c -o part2 2>> s2
if [[ -s s2 ]]
then
    echo There is a compile warning/error.
fi
if [[ ! -x part2 ]] 
then 
    echo part2 executable cannot be generated
    echo part 2 mark is 0
    exit
fi
rm s2 2>/dev/null
./part2 p2.obj > s2 2>/dev/null
if [[  -e s2 ]]
then
    ./compareExamples s2 answer2
fi
rm part2 s2 2>/dev/null

