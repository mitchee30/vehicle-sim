cmake_minimum_required(VERSION 3.14)
project(VehicleSim CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core logic as a library, shared by the main program and the tests
add_library(vehicle_core src/alert.cpp)
target_include_directories(vehicle_core PUBLIC include)

# Main program
add_executable(vehicle_sim src/main.cpp)
target_link_libraries(vehicle_sim vehicle_core)

# Download GoogleTest automatically
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Unit tests
enable_testing()
add_executable(unit_tests tests/test_alert.cpp)
target_link_libraries(unit_tests vehicle_core GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(unit_tests)
