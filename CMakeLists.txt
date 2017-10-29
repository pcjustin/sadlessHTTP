cmake_minimum_required(VERSION 2.6)
project(PaxHTTP NONE)

enable_language(C)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
# add_subdirectory(tools)