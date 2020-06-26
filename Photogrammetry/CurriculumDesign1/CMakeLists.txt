cmake_minimum_required(VERSION 3.10.0)
project(CurriculumDesign VERSION 0.1.0)

add_executable(CurriculumDesign main.cpp widget.h widget.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(CurriculumDesign  PRIVATE Qt5::Widgets Eigen3::Eigen)