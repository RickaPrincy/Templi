#! /bin/bash
cmake -DBUILD_GMOCK=OFF -DINSTALL_GTEST=OFF -DTEMPLI_TEST=ON -S . -B build && cd build; make