#! /bin/bash
git clone https://github.com/RickaPrincy/templi.git
cd templi
mkdir build
cd build
cmake -DTEMPLI_CLI_BUILD=ON -DTEMPLI_CLI_INSTALL=ON -S .. -B .
sudo make install
cd ../..
rm -rf templi