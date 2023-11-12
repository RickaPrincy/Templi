#! /bin/bash
git clone --recursive https://github.com/RickaPrincy
cd Templi
mkdir build
cd build
cmake ..
make
sudo make install
cd ../..