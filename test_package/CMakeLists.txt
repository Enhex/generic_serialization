cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(PackageTest CXX)

find_package(generic_serialization CONFIG REQUIRED)

add_executable(example example.cpp)
target_link_libraries(example generic_serialization::generic_serialization)