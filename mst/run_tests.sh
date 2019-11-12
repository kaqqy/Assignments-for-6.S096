#!/bin/bash
# Simple script to test program on input files and compare to output
# Run in main directory for each assignment to run the tests for that assignment

if [ $(ls | grep -E 'mst-test.x|test_files' | wc -l | tr -d ' ') -ne 2 ]
then
    echo "Missing mst-test.x or test_files/ or running script in wrong directory"
    exit 1
fi

in_files=($(ls test_files/*.in))
for in_file in ${in_files[@]}
do
    prefix="${in_file::${#in_file}-3}"
    cat $in_file | ./mst-test.x > "${prefix}.out2"
    diff "${prefix}.out" "${prefix}.out2" > "${prefix}.diff"
    if [ $(cat ${prefix}.diff | wc -l | tr -d " ") -eq 0 ]
    then
        echo "Passed $in_file"
        rm "${prefix}.out2"
        rm "${prefix}.diff"
    else
        echo "Failed $in_file"
        cat "${prefix}.diff"
        break
    fi
done
