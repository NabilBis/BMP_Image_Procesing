#!/bin/bash

func=""

for path in $(find . -name "compile.txt")
do
    value=$(<$path)
    y=${path%compile*}
    for f in $(echo $value)
    do
        func+="$y$f "
    done
done

cmd="gcc $func -o out"
$cmd
