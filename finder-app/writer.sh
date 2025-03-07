#!/bin/bash

if [ $# -ne 2 ]
then
    echo "usage: ./writer.sh writefile writestr"
    exit 1
fi

writefile=$1
writestr=$2

echo $writestr > $writefile
