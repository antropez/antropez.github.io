#!/bin/sh

for test_file in tests/*.out; do
    printf "Test '%s' starting.\n" $test_file
    $1 ./$test_file
    printf "Test '%s' completed.\n" $test_file
done
