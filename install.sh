#! /bin/bash
git clone https://github.com/RickaPrincy/Templi.git
cd Templi
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .
sudo make install
cd ../..
rm -rf Templi
