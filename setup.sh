#!/bin/sh

file1=$1
file2=$2

cc $file1 -o ${file1%.*}.out
cc $file2 -o ${file2%.*}.out

gnome-terminal --window --title=${file1%.*} -- bash -c "./${file1%.*}.out"
gnome-terminal --window --title=${file2%.*} -- bash -c "./${file2%.*}.out"

exit
