cmake_minimum_required (VERSION 3.8)

project (CarTrack)

find_package( OpenCV REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-return-type -std=c++17")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")
set (build_dir "${PROJECT_SOURCE_DIR}/build/")

file (GLOB source_files "${source_dir}/*.cpp")
file (GLOB additional_files "${source_dir}/*/*.cpp")

add_executable (CarTrack ${source_files} ${additional_files})
target_link_libraries(CarTrack ${OpenCV_LIBS})