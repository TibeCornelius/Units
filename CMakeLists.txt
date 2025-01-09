cmake_minimum_required(VERSION 3.10)
project(PhysicsEngine)

# Specify C++20 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/Source/*.cpp")

add_executable( ${PROJECT_NAME} ${SOURCES})