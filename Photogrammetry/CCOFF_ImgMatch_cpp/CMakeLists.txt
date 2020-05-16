cmake_minimum_required(VERSION 3.16)
project(ImageMatching)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
add_executable(ImageMatching
        ImgMatch.cpp
        ImgMatch.h
        main.cpp)
target_link_libraries(ImageMatching ${OpenCV_LIBS})