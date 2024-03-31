#!/bin/bash

echo End-to-End testing for multiprocess option has started!
echo

files_dir="e2e_test"
#file_list=($(ls $files_dir))
file_list=($files_dir/*)

i=0;
j=19;

while [ $i -le $j ] && [ $(($i + $1)) -le $j ]; do
    args=""
    for ((k=0; k<$1; k++)); do
        args+=" ${file_list[i+k]}"
    done

    echo $args
    ../build/driver_multi $args
    echo

    i=$(($i+$1))
done


