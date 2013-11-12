#!/bin/bash

cd ./scr
make all
cd ..
clear

./scr/testdriver "./data/yieldcurve.txt" "./data/tradingbook_with_spread.txt"
