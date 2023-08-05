@echo off
mkdir build
cd build
cmake -G "Ninja" ..
ninja

REM cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER="C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.36.32532/bin/Hostx64/x64/cl.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.36.32532/bin/Hostx64/x64/cl.exe" -DMSVC_TOOLSET_VERSION=143 .