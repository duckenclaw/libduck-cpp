# enable_clang_tidy(<target>)
# Runs clang-tidy (configured by .clang-tidy) on the target's sources during compilation.
# Opt-in per target so third-party code fetched with FetchContent is never linted.
if(ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_PROGRAM clang-tidy REQUIRED)
  message(STATUS "clang-tidy: ${CLANG_TIDY_PROGRAM}")
  set(CLANG_TIDY_COMMAND "${CLANG_TIDY_PROGRAM}")

  # A non-Apple clang-tidy does not know where the macOS SDK keeps libc++ headers.
  if(APPLE)
    execute_process(
      COMMAND xcrun --show-sdk-path
      OUTPUT_VARIABLE macos_sdk_path
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    list(APPEND CLANG_TIDY_COMMAND "--extra-arg=-isysroot${macos_sdk_path}")
  endif()
endif()

function(enable_clang_tidy target)
  if(ENABLE_CLANG_TIDY)
    set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
  endif()
endfunction()
