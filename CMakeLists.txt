cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_DIR "./src-celaris/build")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")

message(STATUS "Celaris build system initialized.")

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/src-celaris/config.ini" DESTINATION "bin/$<CONFIG>")

add_subdirectory(src-celaris)

message(STATUS "\n|===================================|\n\n    Celaris build complete. \n\n|===================================|")