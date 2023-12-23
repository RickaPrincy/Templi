#! /bin/bash
cmake \
    -DBUILD_GMOCK=OFF \
    -DINSTALL_GTEST=OFF \
    -DTEMPLI_VERSION_BUILD=ON \
    -DTEMPLI_CLI_BUILD=ON \
    -DTEMPLI_CLI_INSTALL=ON \
    -DTEMPLI_LIB_INSTALL=ON \
    -DTEMPLI_TEST=ON \
    -S . -B build 
cd build; sudo make install; cd ..