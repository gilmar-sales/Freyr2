cmake_minimum_required(VERSION 3.15)
project(freyr CXX)

add_library(freyr src/freyr.cpp)
target_include_directories(freyr PUBLIC include)

set_target_properties(freyr PROPERTIES PUBLIC_HEADER "include/freyr.h")
install(TARGETS freyr)
