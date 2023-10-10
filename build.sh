#!/bin/sh

find ./src/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format-18 -style=file -i
mkdir build
cd ./build
cmake --build . --target clean
cmake -G "Ninja" .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
# clang-tidy -p="build" --config-file="../.clang-tidy" ../src/ -extra-arg=-std=c++20
find ../src/ -iname '*.h' -o -iname '*.cpp' | xargs clang-tidy-18 -p="build" --config-file="../.clang-tidy" -extra-arg=-std=c++20
ninja