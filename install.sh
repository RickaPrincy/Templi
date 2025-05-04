#! /bin/bash
git clone -b v4.0.2 https://github.com/RickaPrincy/Templi.git
cd Templi
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .
sudo make install
cd ../..
rm -rf Templi
