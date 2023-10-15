cmake_minimum_required (VERSION 3.8)

project (CarTrack)

# find_package( OpenCV REQUIRED)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wimplicit-fallthrough -Wsign-conversion -std=c++${CMAKE_CXX_STANDARD}")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")
set (build_dir "${PROJECT_SOURCE_DIR}/bin/")
set (CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE
	source_files
	${source_dir}/*.cpp
	${source_dir}/*.h
)

add_executable (CarTrack ${source_files})
target_link_libraries(CarTrack ${OpenCV_LIBS})

set_target_properties(CarTrack PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${build_dir}")
target_compile_options (CarTrack PUBLIC -fexceptions)