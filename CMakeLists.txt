cmake_minimum_required(VERSION 3.16)
project(celaris LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(COPYRIGHT "Copyright 2024, Celaris")
set(VENDOR "Celaris")
set(DESCRIPTION "A C++ desktop application framework using modern frontend technologies.")
set(SHARED_SOURCES)

set(CMAKE_BUILD_DIR "./src-celaris/build")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

enable_testing()

message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

message(STATUS "Celaris build system initialized.")

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/src-celaris/config.ini" DESTINATION "bin/$<CONFIG>")

add_subdirectory(src-celaris)

# Copy config.ini to build directory

foreach(config IN ITEMS Debug Release )#RelWithDebInfo MinSizeRel)
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src-celaris/config.ini"
                   "${CMAKE_BINARY_DIR}/bin/${config}/config.ini"
                   COPYONLY)

# also support the default build type
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src-celaris/config.ini"
                "${CMAKE_BINARY_DIR}/bin/config.ini"
                COPYONLY)

endforeach()

