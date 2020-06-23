cmake_minimum_required(VERSION 3.16.0)
project(Forstner_cpp)

add_executable(Forstner_cpp main.cpp)

# find_package(CImg CONFIG REQUIRED)
# target_link_libraries(Forstner_cpp PRIVATE CImg::CImg)

find_package(OpenCV REQUIRED)
target_link_libraries(Forstner_cpp ${OpenCV_LIBS})
