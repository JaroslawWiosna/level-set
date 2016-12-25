project(test-basic)

file(GLOB src
  "*.cpp"
)
add_executable(${PROJECT_NAME} ${src} ../../Image/Image.cpp )

target_link_libraries(
  ${PROJECT_NAME} 
  ${LINK_FLAGS} 
  ${OpenCV_LIBS} 
)


add_test(${PROJECT_NAME} ${PROJECT_NAME})
