cmake_minimum_required(VERSION 3.22)
project(analysis_method)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(dataFlow_Analysis/Live_Variables)
add_subdirectory(dataFlow_Analysis/available_expr)
