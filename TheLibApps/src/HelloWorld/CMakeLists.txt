# ------------------------
# HelloWorld
# ------------------------
# (No need for 'project()' for a CLI)
set(MODULE_NAME HelloWorld)

# ITK
find_package(ITK NO_MODULE REQUIRED)
include(${ITK_USE_FILE})

# module dependencies
set(${MODULE_NAME}_LIBS ${ITK_LIBRARIES})

# Create the cli
if( ${BUILD_STATIC_CLI} )
  # GenerateCLP
  find_package(GenerateCLP NO_MODULE REQUIRED)
  include(${GenerateCLP_USE_FILE})
  # configure and build
  set(${MODULE_NAME}_SOURCE ${MODULE_NAME}.cxx)
  generateclp(${MODULE_NAME}_SOURCE ${MODULE_NAME}.xml)
  add_executable(${MODULE_NAME} ${${MODULE_NAME}_SOURCE})
  target_link_libraries(${MODULE_NAME} ${${MODULE_NAME}_LIBS})
else()
  # SlicerExecutionModel
  find_package(SlicerExecutionModel NO_MODULE REQUIRED)
  include(${SlicerExecutionModel_USE_FILE})
  # configure and build
  # (call SEMMacroBuildCLI with arg NO_INSTALL to not install)
  SEMMacroBuildCLI(NAME ${MODULE_NAME})
  target_link_libraries(${MODULE_NAME}Lib ${${MODULE_NAME}_LIBS})
endif()
