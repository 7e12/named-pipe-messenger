#!/bin/sh

while getopts lm flags
do
    case "${flags}" in
        l) os="linux";;
        m) os="mac";;
    esac
done

file1=$2
file2=$3

cc $file1 -o ${file1%.*}.out
cc $file2 -o ${file2%.*}.out

if [ $os = "linux" ]
then
    gnome-terminal --window --title=${file1%.*} -- bash -c "./${file1%.*}.out"
    gnome-terminal --window --title=${file2%.*} -- bash -c "./${file2%.*}.out"
elif [ $os = "mac" ]
then
    directory=$(pwd)
    osascript -e 'tell app "Terminal" to do script "'$directory/${file1%.*}.out'"'
    osascript -e 'tell app "Terminal" to do script "'$directory/${file2%.*}.out'"'
else
    echo "OS not found"
    exit
fi

exit
