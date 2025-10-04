cmake_minimum_required(VERSION 3.14)
project(BinomialPricer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pricer src/main.cpp)
target_include_directories(pricer PRIVATE include)
add_executable(runTests tests/main_test.cpp)
target_include_directories(runTests PRIVATE include)
enable_testing()
add_test(NAME PricerTests COMMAND runTests)

