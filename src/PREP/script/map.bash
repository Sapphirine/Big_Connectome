#!/bin/bash 

n=0
while read line ; do
    let n=n+1
    echo "Parameters: $line"
    getKasthuri11 
done
