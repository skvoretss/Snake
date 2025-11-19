cmake_minimum_required(VERSION 3.5)
project(snake)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(GLOB EXE_INCLUDE_FILES ${PROJECT_SOURCE_DIR}/src/*.?pp*)
add_executable(snake ${EXE_INCLUDE_FILES})

target_link_libraries(snake PRIVATE Qt5::Widgets)
