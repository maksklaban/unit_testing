cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project(all)

set (BUILD_SIGNALS_PROCESSOR ON CACHE STRING "Build C++ Signals Processor module.")
set (BUILD_UNIT_TESTS ON CACHE STRING "Build unit tests.")

message ("Components to build:")
message ("  BUILD_SIGNALS_PROCESSOR  = ${BUILD_SIGNALS_PROCESSOR}")

if (BUILD_SIGNALS_PROCESSOR)
  add_subdirectory (signals_buffer)
endif()