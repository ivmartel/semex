# -------------------------------------------------
# TheLibApps: TheLib associated apps
# -------------------------------------------------
project(TheLibApps)

# CMake min
cmake_minimum_required(VERSION 2.8.2)

# pack
set(CPACK_COMPONENTS_ALL RuntimeLibraries)
set(CPACK_PACKAGE_NAME TheLibApps)
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION "v${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "TheLib apps.")
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/dist")
include(CPack)

# build outputs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# All cli should build to this folder
set(SlicerExecutionModel_CLI_RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" CACHE PATH "" FORCE)
set(SlicerExecutionModel_CLI_LIBRARY_OUTPUT_DIRECTORY
  "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" CACHE PATH "" FORCE)
set(SlicerExecutionModel_CLI_ARCHIVE_OUTPUT_DIRECTORY
  "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" CACHE PATH "" FORCE)

# CLI modules list
set(${PROJECT_NAME}_CLI_MODULES HelloWorld HelloImage HelloMask)
# Add the modules
foreach(module ${${PROJECT_NAME}_CLI_MODULES})
  add_subdirectory("src/${module}")
endforeach(module)
