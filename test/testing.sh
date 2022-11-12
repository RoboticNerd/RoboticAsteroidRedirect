#!/bin/bash

rm -rf test.exe;
rm -rf test.o;
g++ -c test.cpp -std=c++98 -O3 -march=native;
g++ test.o -lm -o test;
./test.exe;