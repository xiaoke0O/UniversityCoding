project(test)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_Eigen Eigen_test.cpp)

find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(test_Eigen Eigen3::Eigen )
