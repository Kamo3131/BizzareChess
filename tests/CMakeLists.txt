
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(chess_tests ${TEST_SOURCES} )
target_include_directories(chess_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(chess_tests gtest_main chess_logic)

include(GoogleTest)
gtest_discover_tests(chess_tests)

add_custom_target(run_tests
  COMMAND chess_tests
  DEPENDS chess_tests
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running tests..."
)

