#!/bin/bash

while read -r line
do 
    echo \"$line\"
    rm -rf \"$line\"
done < $1