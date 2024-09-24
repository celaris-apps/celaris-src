cmake_minimum_required(VERSION 3.16)
project(celaris LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)


if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    include(resources/macos/resources.cmake)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include(resources/windows/resources.cmake)
endif()


include(FetchContent)
include(CPack)

# ========= Fetch Libraries ========= #


message(STATUS "Fetching libraries...")

message(STATUS "Fetching webview...")

FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview
    GIT_TAG 0.12.0)
FetchContent_MakeAvailable(webview)

message(STATUS "Fetching nlohmann_json...")

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.3)

FetchContent_MakeAvailable(json)


# ========= Executable ========= #

add_executable(celaris WIN32)
# add_executable(celaris main.cc celaris.cc)
target_sources(celaris PRIVATE main.cc celaris.cc ${SHARED_SOURCES})


target_link_libraries(celaris PRIVATE webview::core)
target_link_libraries(celaris PRIVATE nlohmann_json::nlohmann_json)


add_subdirectory(test)

