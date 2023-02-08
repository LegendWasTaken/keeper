cmake_minimum_required(VERSION 3.20)
project(keeper)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external)

add_executable(keeper source/main.cpp source/cli.h)
target_link_libraries(keeper PRIVATE CLI11::CLI11 -lstdc++)