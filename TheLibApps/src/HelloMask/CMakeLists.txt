# ------------------------
# HelloMask
# ------------------------
# (No need for 'project()' for a CLI)
set(MODULE_NAME HelloMask)

# ITK
find_package(ITK NO_MODULE REQUIRED)
include(${ITK_USE_FILE})

# TheLib
find_package(TheLib NO_MODULE REQUIRED)
include(${TheLib_USE_FILE})

# module dependencies
set(${MODULE_NAME}_LIBS 
  ${ITK_LIBRARIES} TheLib)

# Create the cli
if( ${BUILD_SHARED_LIBS} )
  # SlicerExecutionModel
  find_package(SlicerExecutionModel NO_MODULE REQUIRED)
  include(${SlicerExecutionModel_USE_FILE})
  # configure and build
  SEMMacroBuildCLI(NAME ${MODULE_NAME})
  target_link_libraries(${MODULE_NAME}Lib ${${MODULE_NAME}_LIBS})
else()
  # GenerateCLP
  find_package(GenerateCLP NO_MODULE REQUIRED)
  include(${GenerateCLP_USE_FILE})
  # configure and build
  set(${MODULE_NAME}_SOURCE ${MODULE_NAME}.cxx)
  generateclp(${MODULE_NAME}_SOURCE ${MODULE_NAME}.xml)
  add_executable(${MODULE_NAME} ${${MODULE_NAME}_SOURCE})
  target_link_libraries(${MODULE_NAME} ${${MODULE_NAME}_LIBS})
endif()
