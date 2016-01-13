# ---------------------
# Project TheLib
# ---------------------
project(TheLib)

# CMake min
cmake_minimum_required(VERSION 2.8.2)

# Prerequisites
# ITK
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# build outputs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Include dirs
set(${PROJECT_NAME}_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${${PROJECT_NAME}_INCLUDE_DIRS}")

# Sources and headers
file(GLOB ${PROJECT_NAME}_SRCS 
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB ${PROJECT_NAME}_HEADERS 
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.txx")
  
# Build library
set(${PROJECT_NAME}_LIBNAME ${PROJECT_NAME})
add_library(${${PROJECT_NAME}_LIBNAME} ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_HEADERS})
  
# Configure support files
set(${PROJECT_NAME}_LIBRARY_DIRS "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
set(${PROJECT_NAME}_LIBRARIES ${${PROJECT_NAME}_LIBNAME})
set(${PROJECT_NAME}_USE_FILE
  "${CMAKE_CURRENT_BINARY_DIR}/Use${PROJECT_NAME}.cmake")
# config file
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake")
# use file
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Use${PROJECT_NAME}.cmake.in"
  ${${PROJECT_NAME}_USE_FILE} COPYONLY)

# Testing
if(${BUILD_TESTING})
  include(CTest)
  add_subdirectory(tests)
  # Copy test resource files
  if(${PROJECT_NAME}_COPY_RESOURCES)
    foreach(RES_FILE ${${PROJECT_NAME}_LOCAL_RESOURCES})
      file(COPY ${RES_FILE} 
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/testing")
    endforeach(RES_FILE)
  endif()
endif()
