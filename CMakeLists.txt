cmake_minimum_required(VERSION 3.16)
project(csv_mini_database LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(csv_engine
  src/csv_engine.cpp
)
target_include_directories(csv_engine PUBLIC include)

add_executable(engine
  src/main.cpp
)
target_link_libraries(engine PRIVATE csv_engine)

enable_testing()
add_executable(csv_engine_tests
  tests/test_engine.cpp
)
target_link_libraries(csv_engine_tests PRIVATE csv_engine)
target_compile_definitions(csv_engine_tests PRIVATE
  TEST_DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data/movies.csv"
)
add_test(NAME csv_engine_tests COMMAND csv_engine_tests)
