cmake_minimum_required(VERSION 3.2.1)
project(lab_11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(${PROJECT_NAME}_unit_main unit_tests/check_main.c src/main.c)
target_link_libraries(${PROJECT_NAME}_unit_main ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit_main COMMAND ${PROJECT_NAME}_unit_main WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit_main PROPERTIES TIMEOUT 30)

add_executable(${PROJECT_NAME}_main src/main.c)
target_compile_definitions(${PROJECT_NAME}_main PRIVATE -DENTRY_POINT)

if (USING_VALGRIND)
    include(FindValgrind)

    add_custom_target(Valgrind_${PROJECT_NAME}_unit_main
            COMMAND ${VALGRIND_PROGRAM} --leak-check=full $<TARGET_FILE:${PROJECT_NAME}_unit_main>
            DEPENDS ${PROJECT_NAME}_unit_main
            )
endif (USING_VALGRIND)

