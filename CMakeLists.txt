cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_DIR "./src-celaris/build")

message(STATUS "Celaris build system initialized.")

add_subdirectory(src-cpp)

message(STATUS "\n|===================================|\n\n    Celaris build complete. \n\n|===================================|")