cmake_minimum_required(VERSION 3.10)
project(Rotate_CPP)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(${CMAKE_SOURCE_DIR}/src proj_src)
add_executable(Rotate_CPP ${proj_src})

find_package(OpenCV REQUIRED )
find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(Rotate_CPP Eigen3::Eigen ${OpenCV_LIBS} )

add_subdirectory(test)
enable_testing()
add_test(test_Eigen ${CMAKE_SOURCE_DIR}/build/test/test_Eigen)