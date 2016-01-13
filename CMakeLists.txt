# -----------------------------------------------------
# Project Semex
#
# Example setting for a library with tests and 
#   associated apps using the Slicer Execution Model.
# Uses the CMake External Project to get ITK and SEM.
# -----------------------------------------------------
project( Semex )

cmake_minimum_required( VERSION 2.8.7 )

include( ExternalProject )

# Global options --------------------------------
option(BUILD_SHARED_LIBS "Build shared libraries." OFF)
option(BUILD_TESTING "Build testing." OFF)
# build type (linux)
if(NOT WIN32)
  if(CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "No CMAKE_BUILD_TYPE was provided, setting it to Release.")
    set(CMAKE_BUILD_TYPE "Release")
  endif()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  # activate C++11 (needed for building ITK with gcc5)
  if(CMAKE_COMPILER_IS_GNUCXX)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
  endif()
endif()

# Check GIT
find_package(Git)
if(NOT GIT_FOUND)
  message(ERROR "Cannot find git. git is required for Superbuild.")
endif()
option( USE_GIT_PROTOCOL "If behind a firewall turn this off to use http instead." ON)
set(git_protocol "git")
if(NOT USE_GIT_PROTOCOL)
  set(git_protocol "http")
endif()

# Compute -G arg for configuring external projects with the same CMake
# generator:
if(CMAKE_EXTRA_GENERATOR)
  set(gen "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}")
else()
  set(gen "${CMAKE_GENERATOR}" )
endif()

# ---------------------------------------------------------------------------------------------
# Third parties
# 
# CMake will download the third parties except if one of these var is defined:
# - 'USE_SYSTEM_#': use an installed version
# - '#_DIR': use a locally built version (set when launching cmake: 'cmake -DITK_DIR:PATH=/path/to/itk')

# ITK 
option(USE_SYSTEM_ITK "Build using an installed version of ITK" OFF)
include( ${CMAKE_CURRENT_SOURCE_DIR}/CMakeExternals/External_ITK.cmake )
# SlicerExecutionModel 
option(USE_SYSTEM_SlicerExecutionModel "Build using an installed version of SlicerExecutionModel" OFF)
include( ${CMAKE_CURRENT_SOURCE_DIR}/CMakeExternals/External_SlicerExecutionModel.cmake )

# ---------------------------------------------------------------------------------------------

# TheLib
set(proj TheLib)
message(STATUS "Setting up project: ${proj} (local)" )
ExternalProject_Add(${proj}
  #DEPENDS ITK #error when configuring with ITK_DIR...
  #--Download step--------------
  DOWNLOAD_COMMAND ""
  #--Update/Patch step----------
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  #--Configure step-------------
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${proj}
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DITK_DIR:PATH=${ITK_DIR}
    -DBUILD_TESTING:BOOL=ON
  #--Build step-----------------
  BINARY_DIR ${proj}-build
  #--Test step------------------
  TEST_BEFORE_INSTALL ON
  #--Install step---------------
  INSTALL_COMMAND ""
)
set( ${proj}_DIR ${CMAKE_BINARY_DIR}/${proj}-build )

# TheLibApps
set(proj TheLibApps)
message(STATUS "Setting up project: ${proj} (local)" )
ExternalProject_Add(${proj}
  DEPENDS SlicerExecutionModel TheLib
  #--Download step--------------
  DOWNLOAD_COMMAND ""
  #--Update/Patch step----------
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  #--Configure step-------------
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${proj}
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DITK_DIR:PATH=${ITK_DIR}
    -DSlicerExecutionModel_DIR:PATH=${SlicerExecutionModel_DIR}
    -DTheLib_DIR:PATH=${TheLib_DIR}
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/artifacts
  #--Build step-----------------
  BINARY_DIR ${proj}-build
  #--Install step---------------
  INSTALL_COMMAND ${CMAKE_COMMAND} -DCOMPONENT=RuntimeLibraries -P cmake_install.cmake
)

