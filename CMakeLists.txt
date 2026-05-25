cmake_minimum_required(VERSION 3.28)

project(rzutils CXX)


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

target_compile_features(rzutils PRIVATE cxx_std_23)
target_include_directories(rzutils PUBLIC 
  include/
)
target_link_libraries(rzutils PRIVATE jsonlib)

target_sources(rzutils PRIVATE 
  src/rzutils.cpp
)




