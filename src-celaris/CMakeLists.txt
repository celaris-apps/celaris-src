cmake_minimum_required(VERSION 3.16)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include(FetchContent)
include(CPack)

FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview
    GIT_TAG master)
FetchContent_MakeAvailable(webview)


add_executable(celaris WIN32)
# add_executable(celaris main.cc)
target_sources(celaris PRIVATE main.cc bindings.cc )



target_link_libraries(celaris PRIVATE webview::headers)
