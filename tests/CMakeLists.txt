include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.16.1
  GIT_SHALLOW TRUE
  SYSTEM)
FetchContent_MakeAvailable(Catch2)

add_executable(unit_tests test_ring_buffer.cpp test_ring_buffer_properties.cpp test_stats.cpp)
target_link_libraries(unit_tests PRIVATE core Catch2::Catch2WithMain)
set_project_warnings(unit_tests)
enable_clang_tidy(unit_tests)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(unit_tests)
