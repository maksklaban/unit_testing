cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

# Collect list of all project sources
list (APPEND PROJECT_SOURCES
  signals_buffer.cpp
  network_signals_consumer.cpp
  )

list (APPEND SIGNALS_CONSUMER_INCLUDE_DIRS
  ${PROJECT_SOURCE_DIR}/lib/src
  )
set (SIGNALS_CONSUMER_INCLUDE_DIRS ${SIGNALS_CONSUMER_INCLUDE_DIRS} CACHE STRING "Signals processor Library include directories" )
message ("SIGNALS_CONSUMER_INCLUDE_DIRS = ${SIGNALS_CONSUMER_INCLUDE_DIRS}")

add_library (${PROJECT_STLIB_NAME} STATIC ${PROJECT_SOURCES})
message ("${PROJECT_STLIB_NAME}: Added library target for C++ API.")
