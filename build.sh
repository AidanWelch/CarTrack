#!/bin/sh

mkdir build
cd build
cmake --build . --target clean
cmake -G "Ninja" .. -DCMAKE_BUILD_TYPE=Debug
ninja -d explain