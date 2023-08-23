#!/bin/sh

mkdir build
cd ./build
cmake --build . --target clean
cmake -G "Ninja" .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
ninja -d explain