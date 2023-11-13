#! /bin/bash
git clone --recursive https://github.com/RickaPrincy/Templi.git
cd Templi
mkdir build
cd build
cmake ..
make
sudo make install
cd ../..
