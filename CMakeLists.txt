cmake_minimum_required(VERSION 4.0.0)

project(chess LANGUAGES CXX)
cmake_policy(SET CMP0169 OLD)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

include(FetchContent)

# SFML 2.6.2 (STATIC)
#============================================================================
set(SFML_STATIC_LIBRARIES ON)
set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_TESTS OFF)
set(SFML_BUILD_DOC OFF)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
)
FetchContent_MakeAvailable(SFML)
add_compile_definitions(SFML_STATIC)

#============================================================================
# ImGui (STATIC)
#============================================================================
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.89.9
)
FetchContent_MakeAvailable(imgui)

file(GLOB IMGUI_SRC
    ${imgui_SOURCE_DIR}/*.cpp
)
add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

#============================================================================
# ImGui-SFML (STATIC) — manual build, bypass CMakeLists.txt
#============================================================================
FetchContent_Declare(
    imgui_sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v2.6
)
FetchContent_Populate(imgui_sfml)

add_library(imgui-sfml STATIC
    ${imgui_sfml_SOURCE_DIR}/imgui-SFML.cpp
)

target_include_directories(imgui-sfml PUBLIC
    ${imgui_sfml_SOURCE_DIR}
    ${imgui_SOURCE_DIR}
    ${SFML_SOURCE_DIR}/include
)

target_link_libraries(imgui-sfml PUBLIC
    imgui
    sfml-graphics
    sfml-window
    sfml-system
)

#============================================================================
# Chess project
#============================================================================
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

add_library(chess_logic STATIC ${SOURCES})
target_include_directories(chess_logic PUBLIC ${INCLUDE_DIR})
target_link_libraries(chess_logic PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    imgui
    imgui-sfml
)
add_executable(${PROJECT_NAME} Main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE chess_logic imgui-sfml sfml-graphics sfml-window sfml-system)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 glu32 winmm gdi32)
    target_link_libraries(chess_logic PUBLIC opengl32 glu32 winmm gdi32)
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

enable_testing()
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()