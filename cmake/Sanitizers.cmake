# AddressSanitizer + UndefinedBehaviorSanitizer for GCC/Clang.
# Applied globally so every target (including Catch2) is instrumented consistently.
if(ENABLE_SANITIZERS)
  if(MSVC)
    message(WARNING "ENABLE_SANITIZERS is ignored on MSVC")
  else()
    message(STATUS "Sanitizers: address, undefined")
    set(sanitizer_flags -fsanitize=address,undefined -fno-omit-frame-pointer
                        -fno-sanitize-recover=all)
    add_compile_options(${sanitizer_flags})
    add_link_options(${sanitizer_flags})
  endif()
endif()
