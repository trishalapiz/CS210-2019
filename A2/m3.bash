#!/bin/bash

rm part3 s3 2>/dev/null
gcc part3.c -o part3 2>> s3
if [[ -s s3 ]]
then
    echo There is a compile warning/error.
fi
if [[ ! -x part3 ]] 
then 
    echo part3 executable cannot be generated
    echo part 3 mark is 0
    exit
fi
rm s3 2>/dev/null
./part3 p3.obj > s3 2>/dev/null
if [[  -e s3 ]]
then
    ./compareExamples s3 answer3
fi
rm part3 s3 2>/dev/null

