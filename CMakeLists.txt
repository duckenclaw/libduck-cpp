cmake_minimum_required(VERSION 3.25)

project(
  libduck
  VERSION 0.1.0
  DESCRIPTION "Hand-rolled containers, allocators and concurrency primitives"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:Embedded>")
endif()

option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)
option(ENABLE_SANITIZERS "Build with AddressSanitizer and UndefinedBehaviorSanitizer" OFF)
option(ENABLE_CLANG_TIDY "Run clang-tidy on project sources while compiling" OFF)
option(BUILD_TESTING "Build the unit tests" ON)
option(DUCK_BUILD_BENCHMARKS "Build the Google Benchmark suite" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Ccache)
include(CompilerWarnings)
include(Sanitizers)
include(ClangTidy)

add_library(duck src/version.cpp)
add_library(duck::duck ALIAS duck)
target_include_directories(duck PUBLIC include)
target_compile_features(duck PUBLIC cxx_std_20)
target_compile_definitions(duck PRIVATE DUCK_VERSION="${PROJECT_VERSION}")
set_project_warnings(duck)
enable_clang_tidy(duck)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

if(DUCK_BUILD_BENCHMARKS)
  add_subdirectory(bench)
endif()
