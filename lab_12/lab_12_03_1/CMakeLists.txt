cmake_minimum_required(VERSION 3.2.1)
project(lab_12_03_1)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_library(${PROJECT_NAME}_shared SHARED ../_src/main.c src/filter.c)
add_library(${PROJECT_NAME}_static STATIC ../_src/main.c src/filter.c)

add_executable(${PROJECT_NAME}_unit unit_tests/check_filter.c)
target_compile_definitions(${PROJECT_NAME}_unit PRIVATE -DPROJECT_NAME="${PROJECT_NAME}")
target_link_libraries(${PROJECT_NAME}_unit ${CHECK_LIBRARIES} ${PROJECT_NAME}_static  ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit COMMAND ${PROJECT_NAME}_unit WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit PROPERTIES TIMEOUT 30)
