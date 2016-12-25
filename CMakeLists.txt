cmake_minimum_required(VERSION 2.8)

#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})
project( DisplayImage )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package( OpenCV REQUIRED )
add_executable( level-set main.cpp Image/Image.cpp )
target_link_libraries( level-set ${OpenCV_LIBS} )

option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 11)
set(COMPILE_FLAGS "-Wall -Wno-missing-braces")
set(GTEST_FLAGS "-lgtest")
set(LINK_FLAGS "-lpthread")

if(BUILD_TESTS)
	include_directories(${GTEST_INCLUDE_DIRS})
endif()
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(Image)

enable_testing()
if(BUILD_TESTS)
	find_package(Gtest)
endif()

if(BUILD_TESTS)
	set(LINK_FLAGS "${GTEST_FLAGS} ${LINK_FLAGS}")
endif()

if(BUILD_TESTS)
	add_subdirectory(gtest)
endif()


