cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package( OpenCV REQUIRED )
add_executable( level-set main.cpp )
target_link_libraries( level-set ${OpenCV_LIBS} )

option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 11)
set(COMPILE_FLAGS "-Wall -Wno-missing-braces")
set(GTEST_FLAGS "-lgtest")
set(LINK_FLAGS "-lpthread")

include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()
find_package(Gtest)

if(BUILD_TESTS)
	set(LINK_FLAGS "${GTEST_FLAGS} ${LINK_FLAGS}")
endif()

if(BUILD_TESTS)
  add_subdirectory(gtest)
endif()


