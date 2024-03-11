cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project(signals_buffer)

set (PROJECT_SHLIB_NAME ${PROJECT_NAME})
set (PROJECT_STLIB_NAME ${PROJECT_NAME}_static)
set (PROJECT_UTEST_NAME ${PROJECT_NAME}_test)

add_subdirectory(lib)

#if (BUILD_DOC)
#  add_subdirectory(doc)
#endif()