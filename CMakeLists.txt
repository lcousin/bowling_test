cmake_minimum_required(VERSION 3.0)

project(BowlingTest CXX)

find_package(Threads REQUIRED)

include_directories(include)
file(GLOB SRC_MAIN "src/*.cpp")

add_executable(bowling_score ${SRC_MAIN})

file(GLOB SRC_TESTS "test/*.cpp")

set(SRC_GTEST "3rdparty/googletest-master/googletest/")
file(GLOB GTEST_LIBS "3rdparty/googletest-master/googletest/*.a")

include_directories("3rdparty/googletest-master/googletest/include")


add_executable(bowling_tests ${SRC_GTEST} ${SRC_TESTS} "src/bowling.cpp")
target_link_libraries(bowling_tests ${GTEST_LIBS} pthread)
