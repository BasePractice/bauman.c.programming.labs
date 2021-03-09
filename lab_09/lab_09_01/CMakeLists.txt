cmake_minimum_required(VERSION 3.2.1)
project(lab_09_01)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(${PROJECT_NAME}_main ../_src/main.c src/main.c)
target_compile_definitions(${PROJECT_NAME}_main PRIVATE -DENTRY_POINT)