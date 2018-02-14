#!/bin/bash

for filename in *.txt; do
    printf "Testing $filename:\n";
    ./earliestMeeting $filename;
    printf "\n";
done
