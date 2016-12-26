#
# @par Licence
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#


project(test-flagparser)

file(GLOB src
  "*.cpp"
)
add_executable(${PROJECT_NAME} ${src} ../../FlagParser/FlagParser.cpp )

target_link_libraries(
  ${PROJECT_NAME} 
  ${LINK_FLAGS} 
  ${OpenCV_LIBS} 
)


add_test(${PROJECT_NAME} ${PROJECT_NAME})
