#!/bin/bash

rm -rf main.exe;
rm -rf main.o;
rm -rf hohmann.png;
rm -rf h_time.png;
g++ -c main.cpp -std=c++98 -O3 -march=native;
g++ main.o -lm -o main;
./main.exe;