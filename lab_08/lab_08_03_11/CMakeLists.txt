cmake_minimum_required(VERSION 3.2.1)
project(lab_08_03_11)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(${PROJECT_NAME}_main ../_src/main.c ../_src/format.c ../_src/format_plain.c src/main.c)
target_compile_definitions(${PROJECT_NAME}_main PRIVATE -DENTRY_POINT -DFORMAT_PLAIN)
target_link_libraries(${PROJECT_NAME}_main PRIVATE ${DEPENDENCY_LIBRARIES})

add_executable(${PROJECT_NAME}_unit_main unit_tests/check_main.c  ../_src/format.c  ../_src/format_plain.c ../_src/main.c src/main.c)
target_compile_definitions(${PROJECT_NAME}_unit_main PRIVATE -DDEBUG_PRINT0 -DFORMAT_PLAIN)
target_link_libraries(${PROJECT_NAME}_unit_main ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit_main COMMAND ${PROJECT_NAME}_unit_main WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit_main PROPERTIES TIMEOUT 30)