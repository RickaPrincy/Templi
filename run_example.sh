#! /bin/bash
cd example
touch main.cpp
cmake -S . -B build
cd build; make
./example
cd ../..