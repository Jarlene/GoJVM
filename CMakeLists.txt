cmake_minimum_required(VERSION 3.14)
project(GoJVM)


find_package(JNI REQUIRED)

include_directories(${JNI_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

#add_library(GoJVM jvm_interface.h jvm_interface.cpp)
#target_link_libraries(GoJVM ${JNI_LIBRARIES})

add_executable(GoJVM main.cpp JvmInterface.cpp JvmInterface.h)
target_link_libraries(GoJVM  ${JNI_LIBRARIES})