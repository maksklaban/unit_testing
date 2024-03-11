cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

set(GTEST_ROOT "/home/mklaban/cloudmade/education/unit_tests/external/gtest_build/install/lib")
find_package(GTest REQUIRED)

add_executable(${PROJECT_UTEST_NAME} tests.cpp)

target_link_libraries(${PROJECT_UTEST_NAME} PRIVATE ${PROJECT_STLIB_NAME} GTest::gtest GTest::gtest_main)
target_include_directories(${PROJECT_UTEST_NAME} PRIVATE ${SIGNALS_CONSUMER_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})