#!/bin/bash

cd ./scr
make
cd ..
clear

DATA="./data/*.txt"
for file in $DATA
do
	echo "=========================";
	echo "Running file: ${file##*/}";
	echo "=========================";
	./scr/testdriver "./data/${file##*/}";
done