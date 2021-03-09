cmake_minimum_required(VERSION 3.2.1)
project(lab_07)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/_inc)

add_executable(${PROJECT_NAME}_unit_main _unit_tests/check_main.c _src/main.c)
target_link_libraries(${PROJECT_NAME}_unit_main ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit_main COMMAND ${PROJECT_NAME}_unit_main WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit_main PROPERTIES TIMEOUT 30)
# Проверка сортировки №1
add_executable(${PROJECT_NAME}_unit_sort_01 _unit_tests/check_sort.c _src/sort_01.c _src/main.c)
target_link_libraries(${PROJECT_NAME}_unit_sort_01 ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit_sort_01 COMMAND ${PROJECT_NAME}_unit_sort_01 WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit_sort_01 PROPERTIES TIMEOUT 30)
# Проверка сортировки №2
add_executable(${PROJECT_NAME}_unit_sort_02 _unit_tests/check_sort.c _src/sort_02.c _src/main.c)
target_compile_definitions(${PROJECT_NAME}_unit_sort_02 PRIVATE -DRIGHT)
target_link_libraries(${PROJECT_NAME}_unit_sort_02 ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit_sort_02 COMMAND ${PROJECT_NAME}_unit_sort_02 WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit_sort_02 PROPERTIES TIMEOUT 30)
# Проверка сортировки №3
add_executable(${PROJECT_NAME}_unit_sort_03 _unit_tests/check_sort.c _src/sort_03.c _src/main.c)
target_compile_definitions(${PROJECT_NAME}_unit_sort_03 PRIVATE -DRIGHT)
target_link_libraries(${PROJECT_NAME}_unit_sort_03 ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit_sort_03 COMMAND ${PROJECT_NAME}_unit_sort_03 WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit_sort_03 PROPERTIES TIMEOUT 30)
# Проверка сортировки №4
add_executable(${PROJECT_NAME}_unit_sort_04 _unit_tests/check_sort.c _src/sort_04.c _src/main.c)
target_compile_definitions(${PROJECT_NAME}_unit_sort_04 PRIVATE -DRIGHT)
target_link_libraries(${PROJECT_NAME}_unit_sort_04 ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit_sort_04 COMMAND ${PROJECT_NAME}_unit_sort_04 WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit_sort_04 PROPERTIES TIMEOUT 30)
# Проверка сортировки №5
add_executable(${PROJECT_NAME}_unit_sort_05 _unit_tests/check_sort.c _src/sort_05.c _src/main.c)
target_compile_definitions(${PROJECT_NAME}_unit_sort_05 PRIVATE -DRIGHT)
target_link_libraries(${PROJECT_NAME}_unit_sort_05 ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit_sort_05 COMMAND ${PROJECT_NAME}_unit_sort_05 WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit_sort_05 PROPERTIES TIMEOUT 30)
# Проверка сортировки №6
add_executable(${PROJECT_NAME}_unit_sort_06 _unit_tests/check_sort.c _src/sort_06.c _src/main.c)
target_compile_definitions(${PROJECT_NAME}_unit_sort_06 PRIVATE -DRIGHT)
target_link_libraries(${PROJECT_NAME}_unit_sort_06 ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit_sort_06 COMMAND ${PROJECT_NAME}_unit_sort_06 WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit_sort_06 PROPERTIES TIMEOUT 30)
# Проверка сортировки №7
add_executable(${PROJECT_NAME}_unit_sort_07 _unit_tests/check_sort.c _src/sort_07.c _src/main.c)
target_compile_definitions(${PROJECT_NAME}_unit_sort_07 PRIVATE -DRIGHT)
target_link_libraries(${PROJECT_NAME}_unit_sort_07 ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit_sort_07 COMMAND ${PROJECT_NAME}_unit_sort_07 WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit_sort_07 PROPERTIES TIMEOUT 30)

if (USING_VALGRIND)
    include(FindValgrind)

    add_custom_target(Valgrind_${PROJECT_NAME}_unit_main
            COMMAND ${VALGRIND_PROGRAM} --leak-check=full $<TARGET_FILE:${PROJECT_NAME}_unit_main>
            DEPENDS ${PROJECT_NAME}_unit_main
            )
endif (USING_VALGRIND)

add_subdirectory(lab_07_01)
add_subdirectory(lab_07_02)
add_subdirectory(lab_07_03)
add_subdirectory(lab_07_04)
add_subdirectory(lab_07_05)
