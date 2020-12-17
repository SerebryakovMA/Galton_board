cmake_minimum_required(VERSION 3.0.0)
project(galton VERSION 0.1.0)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(galton main.cpp)
target_link_libraries(galton ${PYTHON_LIBRARIES})