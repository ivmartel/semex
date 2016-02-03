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

# SlicerExecutionModel
find_package(SlicerExecutionModel NO_MODULE REQUIRED)
include(${SlicerExecutionModel_USE_FILE})
# configure and build
# @param NO_INSTALL Do not add the cli to the install list
SEMMacroBuildCLI(NAME ${MODULE_NAME})
# link to library
target_link_libraries(${MODULE_NAME}Lib ${${MODULE_NAME}_LIBS})

