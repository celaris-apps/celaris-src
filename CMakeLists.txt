cmake_minimum_required(VERSION 3.16)
project(celaris LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_DIR "./src-celaris/build")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")

message(STATUS "Celaris build system initialized.")

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/src-celaris/config.ini" DESTINATION "bin/$<CONFIG>")

add_subdirectory(src-celaris)

foreach(config IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src-celaris/config.ini"
                   "${CMAKE_BINARY_DIR}/bin/${config}/config.ini"
                   COPYONLY)
endforeach()

message(STATUS "\n|===================================|\n\n    Celaris build complete. \n\n|===================================|")