cmake_minimum_required (VERSION 3.8)

project (CarTrack)

# find_package( OpenCV REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -std=c++20")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")
set (build_dir "${PROJECT_SOURCE_DIR}/bin/")
set (CMAKE_CXX_STANDARD 20)
set (CXX_STANDARD_REQUIRED ON)

file (GLOB source_files "${source_dir}/*.cpp")
file (GLOB additional_files "${source_dir}/*/*.cpp")

add_executable (CarTrack ${source_files} ${additional_files})
target_link_libraries(CarTrack ${OpenCV_LIBS})

set_target_properties(CarTrack PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${build_dir}")
target_compile_options (CarTrack PUBLIC -fexceptions)