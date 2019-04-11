#!/bin/bash
palette="palette.png"

filters="fps=$3"
echo "file '$1'" > files.txt
echo "file 'reversed.mkv'" >> files.txt
ffmpeg -framerate $3 -i out%d.png -crf 0 -y $1
cp $1 "$1".copy
ffmpeg -i $1 -vf reverse -crf 0 -y reversed.mkv
mv "$1".copy $1
ffmpeg  -f concat -safe 0 -i files.txt -c copy -y comb"$1"
mv comb"$1" $1
#ffmpeg -i $1 -i reversed.mkv -crf 0 -filter_complex "[0:v] [1:v]  concat=n=2:v=1 [v]" -map "[v]" $1
ffmpeg -v warning -i $1 -vf "$filters,palettegen" -y $palette
ffmpeg -v warning -i $1 -i $palette -lavfi "$filters [x]; [x][1:v] paletteuse" -y $2
