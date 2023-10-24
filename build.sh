#!/bin/sh

find ./src/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format-18 -style=file -i
mkdir build
cd ./build
cmake --build . --target clean
cmake -G "Ninja" .. -D CMAKE_BUILD_TYPE=$1 -D CMAKE_EXPORT_COMPILE_COMMANDS=ON
find ../src/ -iname '*.h' -o -iname '*.cpp' | xargs clang-tidy-18 -p="build" --config-file="../.clang-tidy" -extra-arg=-std=c++20
ninja