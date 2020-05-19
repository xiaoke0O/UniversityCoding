cmake_minimum_required(VERSION 3.10)
project(Rotate_CPP)

set(CMAKE_CXX_STANDARD 14)

add_executable(Rotate_CPP main.cpp resample.h resample.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(Rotate_CPP ${OpenCV_LIBS})