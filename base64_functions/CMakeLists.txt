cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project(base64_functions_tests)

set(GTEST_ROOT "/home/mklaban/cloudmade/education/unit_tests/external/gtest_build/install/lib")
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} base64_functions.cpp tests.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PRIVATE ${GTEST_INCLUDE_DIRS})