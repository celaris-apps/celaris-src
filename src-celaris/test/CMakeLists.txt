cmake_minimum_required(VERSION 3.16)
project(celaris LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)


add_executable(tests test.cc)
target_link_libraries(tests GTest::gtest_main)
target_link_libraries(tests nlohmann_json::nlohmann_json)
target_link_libraries(tests webview::core)

include(GoogleTest)
gtest_discover_tests(tests)
