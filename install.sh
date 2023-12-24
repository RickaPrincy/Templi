#! /bin/bash
git clone https://github.com/RickaPrincy/Templi.git
cd Templi
git submodule update --init external/TColor 
git submodule update --init external/RCli
mkdir build
cd build
cmake -DTEMPLI_CLI_BUILD=ON -DTEMPLI_CLI_INSTALL=ON -S .. -B .
sudo make install
cd ../..
rm -rf Templi