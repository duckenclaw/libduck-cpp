# AddressSanitizer + UndefinedBehaviorSanitizer, or ThreadSanitizer, for GCC/Clang.
# Applied globally so every target (including Catch2) is instrumented consistently.
option(ENABLE_TSAN "Build with ThreadSanitizer" OFF)

if(ENABLE_SANITIZERS AND ENABLE_TSAN)
  message(FATAL_ERROR "ENABLE_SANITIZERS and ENABLE_TSAN can't be combined, use separate presets")
endif()

if(ENABLE_SANITIZERS OR ENABLE_TSAN)
  if(MSVC)
    message(WARNING "sanitizers are ignored on MSVC")
  else()
    if(ENABLE_TSAN)
      message(STATUS "Sanitizers: thread")
      set(sanitizer_flags -fsanitize=thread)
    else()
      message(STATUS "Sanitizers: address, undefined")
      set(sanitizer_flags -fsanitize=address,undefined -fno-sanitize-recover=all)
    endif()
    list(APPEND sanitizer_flags -fno-omit-frame-pointer)
    add_compile_options(${sanitizer_flags})
    add_link_options(${sanitizer_flags})
  endif()
endif()
