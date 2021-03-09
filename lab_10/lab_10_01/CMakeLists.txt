cmake_minimum_required(VERSION 3.2.1)
project(lab_10_01)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(${PROJECT_NAME}_main ../_src/main.c src/main.c src/fn_find.c src/fn_pop_front.c src/fn_pop_back.c src/fn_insert.c src/fn_copy.c src/fn_append.c src/fn_remove_duplicates.c src/fn_reverse.c src/fn_sort.c)
target_compile_definitions(${PROJECT_NAME}_main PRIVATE -DENTRY_POINT)

add_executable(${PROJECT_NAME}_unit ../_src/main.c unit_tests/check_main.c src/fn_find.c src/fn_pop_front.c src/fn_pop_back.c src/fn_insert.c src/fn_copy.c src/fn_append.c src/fn_remove_duplicates.c src/fn_reverse.c src/fn_sort.c)
target_compile_definitions(${PROJECT_NAME}_unit PRIVATE -DRIGHT)
target_link_libraries(${PROJECT_NAME}_unit ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit COMMAND ${PROJECT_NAME}_unit WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit PROPERTIES TIMEOUT 30)