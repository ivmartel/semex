# --------------------------
# Tests of TheLib
# --------------------------

# test files
file(GLOB ${PROJECT_NAME}_TEST_SRCS 
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# test data
set(TEST_DATA_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/data")
 
# create executable and add as test
foreach(TEST_SRC ${${PROJECT_NAME}_TEST_SRCS})
  get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
  add_executable(${TEST_NAME} ${TEST_SRC})
  target_link_libraries(${TEST_NAME} 
    ${ITK_LIBRARIES} TheLib)
  add_test(NAME ${TEST_NAME} 
    COMMAND $<TARGET_FILE:${TEST_NAME}> ${TEST_DATA_FOLDER})
endforeach(TEST_SRC)
