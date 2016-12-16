cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package( OpenCV REQUIRED )
add_executable( DisplayImage DisplayImage.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )
add_executable( main main.cpp )
target_link_libraries( main ${OpenCV_LIBS} )

option(BUILD_TESTS "Build tests" ON)

include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()
find_package(Gtest)

if(BUILD_TESTS)
  add_subdirectory(tst)
endif()


