cmake_minimum_required(VERSION 3.10)
project(UnitsLibrary)

# Specify C++20 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Default to Debug build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add a custom option to control the "Random" macro
option(ENABLE_RANDOM "Enable the 'Random' macro" OFF)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/Source/*.cpp")

add_executable( ${PROJECT_NAME} ${SOURCES})

# Conditionally add the compile definition
if(SEMI_UNIT_SAFETY)
message("ENABLE_RANDOM is ON")
# Define compile definitions (only after the target is created)
target_compile_definitions(${PROJECT_NAME} PRIVATE SEMI_UNIT_SAFETY)
else()
message("ENABLE_RANDOM is OFF")
endif()

