cmake_minimum_required(VERSION 3.10)

project(chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

include_directories(${INCLUDE_DIR})

file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

add_library(chess_logic STATIC ${SOURCES})
target_include_directories(chess_logic PUBLIC ${INCLUDE_DIR})

add_executable(${PROJECT_NAME} Main.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME} chess_logic)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

enable_testing()
add_subdirectory(tests)