cmake_minimum_required(VERSION 3.10)
project(pacman)

# Find SDL2
find_package(SDL2 REQUIRED)

# Include SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Include directory
include_directories(include)

# Source files
file(GLOB SOURCES src/*.cpp)

# Create executable
add_executable(pacman ${SOURCES})

# Link SDL2 libraries
target_link_libraries(pacman ${SDL2_LIBRARIES})
