#! /bin/bash
git clone https://github.com/RickaPrincy/Templi.git
cd Templi
git submodule update --init external/TColor 
mkdir build
cd build
cmake ..
make
sudo make install
cd ../..
rm -rf Templi