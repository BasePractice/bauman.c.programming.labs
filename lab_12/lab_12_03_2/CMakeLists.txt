cmake_minimum_required(VERSION 3.2.1)
project(lab_12_03_2)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_library(${PROJECT_NAME} SHARED ../_src/main.c src/functions.c)

add_executable(${PROJECT_NAME}_unit ../_src/main.c unit_tests/check_functions.c)
target_compile_definitions(${PROJECT_NAME}_unit PRIVATE -DPROJECT_NAME="${PROJECT_NAME}")
target_link_libraries(${PROJECT_NAME}_unit ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit COMMAND ${PROJECT_NAME}_unit WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit PROPERTIES TIMEOUT 30)
