cmake_minimum_required(VERSION 3.20)
project(keeper)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external)

add_library(keeper source/cli.cpp)
target_link_libraries(keeper PUBLIC CLI11::CLI11 -lstdc++)

add_executable(keeper-driver source/main.cpp)
target_link_libraries(keeper-driver PRIVATE keeper)

add_executable(keeper-tests test/cli.h)
target_link_libraries(keeper-tests PRIVATE keeper Catch2::Catch2WithMain)