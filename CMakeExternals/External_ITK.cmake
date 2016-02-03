set(proj ITK)

# sanity checks
if(DEFINED ${proj}_DIR AND NOT EXISTS ${${proj}_DIR})
  message(FATAL_ERROR "${proj}_DIR variable is defined but corresponds to nonexistent directory.")
endif()

# add external project
if(NOT DEFINED ${proj}_DIR AND NOT USE_SYSTEM_${proj})
  set(${proj}_REPO ${git_protocol}://itk.org/ITK.git)
  # ITK v4.7 needs:
  # - cmake 2.8.6 or higher on linux, 2.8.8 or higher on windows
  # - does not build with gcc5 (vcl compiler check)
  # ITK v4.8 needs cmake 2.8.9 or higher
  # ITK v4.9.0 needs cmake 2.8.9 or higher
  if(CMAKE_VERSION VERSION_LESS 2.8.9)
    set(${proj}_TAG v4.7.2)
  else()
    set(${proj}_TAG v4.9.0)
  endif()

  message(STATUS "Setting up external project: ${proj} (${${proj}_TAG})" )

  ExternalProject_Add(${proj}
    #--Download step--------------
    GIT_REPOSITORY "${${proj}_REPO}"
    GIT_TAG "${${proj}_TAG}"
    #--Update/Patch step----------
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    #--Configure step-------------
    SOURCE_DIR ${proj}
    CMAKE_GENERATOR ${gen}
    CMAKE_ARGS
      -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
      -DBUILD_EXAMPLES:BOOL=OFF
      -DBUILD_SHARED_LIBS:BOOL=ON
      -DBUILD_TESTING:BOOL=OFF
      -DITK_LEGACY_REMOVE:BOOL=ON
      -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
    #--Build step-----------------
    BINARY_DIR ${proj}-build
    #--Install step---------------
    INSTALL_COMMAND ""
  )
  set( ${proj}_DIR ${CMAKE_BINARY_DIR}/${proj}-build )
endif()
