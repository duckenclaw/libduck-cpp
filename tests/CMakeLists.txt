include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.16.1
  GIT_SHALLOW TRUE
  SYSTEM)
FetchContent_MakeAvailable(Catch2)

add_executable(duck_tests test_version.cpp)
target_link_libraries(duck_tests PRIVATE duck::duck Catch2::Catch2WithMain)
set_project_warnings(duck_tests)
enable_clang_tidy(duck_tests)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(duck_tests)
