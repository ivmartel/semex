set(proj SlicerExecutionModel)

# sanity checks
if(DEFINED ${proj}_DIR AND NOT EXISTS ${${proj}_DIR})
  message(FATAL_ERROR "${proj}_DIR variable is defined but corresponds to nonexistent directory.")
endif()

# add external project
if(NOT DEFINED ${proj}_DIR AND NOT ${CMAKE_PROJECT_NAME}_USE_SYSTEM_${proj})
  set(${proj}_REPO ${git_protocol}://github.com/Slicer/SlicerExecutionModel.git)
  # version of Oct 28, 2015
  set(${proj}_TAG 311eff9)

  message(STATUS "Setting up external project: ${proj} (${${proj}_TAG})" )

  ExternalProject_Add(${proj}
    #DEPENDS ITK #error when configuring with ITK_DIR...
    #--Download step--------------
    GIT_REPOSITORY "${${proj}_REPO}"
    GIT_TAG "${${proj}_TAG}"
    #--Update/Patch step----------
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    #--Configure step-------------
    SOURCE_DIR ${proj}
    CMAKE_ARGS
      -DITK_DIR:PATH=${ITK_DIR}
       # avoid instaling lib files for windows
      -DSlicerExecutionModel_DEFAULT_CLI_INSTALL_ARCHIVE_DESTINATION:PATH=
    #--Build step-----------------
    BINARY_DIR ${proj}-build
    #--Install step---------------
    INSTALL_COMMAND ""
  )
  set( ${proj}_DIR ${CMAKE_BINARY_DIR}/${proj}-build )
endif()

