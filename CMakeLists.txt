cmake_minimum_required(VERSION 3.10)
project(BezierSpline)

set(CMAKE_CXX_STANDARD 11)

# Find Eigen3 in the standard installation directories
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(${PROJECT_NAME} main.cpp BezierSpline.cpp)

# Link your application with Eigen
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)
