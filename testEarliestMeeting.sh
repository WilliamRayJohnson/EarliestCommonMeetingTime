#!/bin/bash

for filename in sets/*.txt; do
    printf "Testing $filename:\n";
    ./earliestMeeting $filename;
    printf "\n";
done
