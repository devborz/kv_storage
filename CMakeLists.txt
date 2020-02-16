cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
  SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)

project(kv_storage)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
hunter_add_package(Boost COMPONENTS program_options
thread filesystem)
find_package(Boost CONFIG REQUIRED program_options
thread filesystem)
find_package(GTest CONFIG REQUIRED)

add_library(kv_storage INTERFACE
)
add_library(PicoSHA2 INTERFACE
)
add_executable(tests
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
)

target_include_directories(kv_storage 
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(PicoSHA2
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/PicoSHA2/
)
target_include_directories(tests 
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(kv_storage INTERFACE PicoSHA2)
target_link_libraries(tests GTest::main kv_storage)

enable_testing()
add_test(NAME unit_tests COMMAND tests) 