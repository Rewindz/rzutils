cmake_minimum_required(VERSION 3.28)

project(rzutils CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(json
  URL https://github.com/nlohmann/json/releases/download/v3.12.0/include.zip
)

FetchContent_MakeAvailable(json)

add_library(jsonlib INTERFACE)
target_include_directories(jsonlib INTERFACE
  "${json_SOURCE_DIR}/single_include"
)

add_library(rzutils STATIC)

target_compile_features(rzutils PUBLIC cxx_std_23)
target_include_directories(rzutils PUBLIC
  include/
)
target_link_libraries(rzutils PUBLIC jsonlib)

set(RZ_HEADER_DIR "${CMAKE_SOURCE_DIR}/include/rz")
set(RZ_SRC_DIR "${CMAKE_SOURCE_DIR}/src")

target_sources(rzutils PRIVATE
  "${RZ_SRC_DIR}/fs.cpp"
  "${RZ_SRC_DIR}/saveable.cpp"
  "${RZ_HEADER_DIR}/defs/defs.hpp"
  "${RZ_HEADER_DIR}/fs/fs.hpp"
  "${RZ_HEADER_DIR}/json/json.hpp"
  "${RZ_HEADER_DIR}/json/saveable.hpp"
  "${RZ_HEADER_DIR}/math/math.hpp"
  "${RZ_HEADER_DIR}/math/mat.hpp"
  "${RZ_HEADER_DIR}/math/vec.hpp"
  "${RZ_HEADER_DIR}/math/quat.hpp"
)

if(RZ_BUILD_CXX_MODULES)
  target_sources(rzutils PUBLIC
    FILE_SET CXX_MODULES
    FILES
      src/rzutils.cppm
  )
endif()

enable_testing()

FetchContent_Declare(googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(rzutils_tests
  tests/test_math.cpp
  tests/test_json.cpp
)

target_link_libraries(rzutils_tests PRIVATE
  rzutils
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(rzutils_tests)
