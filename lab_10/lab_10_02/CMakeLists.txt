cmake_minimum_required(VERSION 3.2.1)
project(lab_10_02)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(${PROJECT_NAME}_01_main ../_src/main.c src/main01.c src/menu.c src/value.c)
add_executable(${PROJECT_NAME}_02_main ../_src/main.c src/main02.c src/menu.c src/value.c)
add_executable(${PROJECT_NAME}_03_main ../_src/main.c src/main03.c src/menu.c src/value.c)
add_executable(${PROJECT_NAME}_04_main ../_src/main.c src/main04.c src/menu.c src/value.c)
add_executable(${PROJECT_NAME}_05_main ../_src/main.c src/main05.c src/menu.c src/value.c src/text.c)

target_link_libraries(${PROJECT_NAME}_01_main PRIVATE ${DEPENDENCY_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_02_main PRIVATE ${DEPENDENCY_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_03_main PRIVATE ${DEPENDENCY_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_04_main PRIVATE ${DEPENDENCY_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_05_main PRIVATE ${DEPENDENCY_LIBRARIES})

add_executable(${PROJECT_NAME}_unit ../_src/main.c  src/value.c src/text.c  unit_tests/check_main.c)
target_compile_definitions(${PROJECT_NAME}_unit PRIVATE -DRIGHT)
target_link_libraries(${PROJECT_NAME}_unit ${CHECK_LIBRARIES} ${DEPENDENCY_LIBRARIES})
add_test(NAME ${PROJECT_NAME}_unit COMMAND ${PROJECT_NAME}_unit WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${PROJECT_NAME}_unit PROPERTIES TIMEOUT 30)