cmake_minimum_required(VERSION 3.20)
project(keeper-web)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external)

add_library(keeper source/cli.cpp)
target_link_libraries(keeper PUBLIC CLI11::CLI11)
target_include_directories(keeper PUBLIC external)

add_executable(keeper-driver source/main.cpp)
target_link_libraries(keeper-driver PRIVATE keeper)

add_executable(keeper-tests test/cli.cpp test/config.cpp)
target_link_libraries(keeper-tests PRIVATE keeper Catch2::Catch2WithMain)
target_include_directories(keeper-tests PRIVATE source)
catch_discover_tests(keeper-tests)