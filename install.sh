#! /bin/bash
git clone -b v3.2.0 https://github.com/RickaPrincy/Templi.git
cd Templi
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .
sudo make install
cd ../..
rm -rf Templi
