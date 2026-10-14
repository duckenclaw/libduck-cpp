# set_project_warnings(<target>)
# Applies a strict warning set to one of our own targets (never to third-party code).
function(set_project_warnings target)
  set(msvc_warnings /W4 /permissive- /w14242 /w14254 /w14263 /w14265 /w14287 /w14296 /w14311
                    /w14545 /w14546 /w14547 /w14549 /w14555 /w14640 /w14826 /w14928)

  set(clang_warnings
      -Wall
      -Wextra
      -Wpedantic
      -Wshadow
      -Wnon-virtual-dtor
      -Wold-style-cast
      -Wcast-align
      -Wunused
      -Woverloaded-virtual
      -Wconversion
      -Wsign-conversion
      -Wnull-dereference
      -Wdouble-promotion
      -Wformat=2
      -Wimplicit-fallthrough)

  set(gcc_warnings ${clang_warnings} -Wmisleading-indentation -Wduplicated-cond
                   -Wduplicated-branches -Wlogical-op -Wuseless-cast)

  if(WARNINGS_AS_ERRORS)
    list(APPEND msvc_warnings /WX)
    list(APPEND clang_warnings -Werror)
    list(APPEND gcc_warnings -Werror)
  endif()

  if(MSVC)
    set(warnings ${msvc_warnings})
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(warnings ${clang_warnings})
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(warnings ${gcc_warnings})
  endif()

  target_compile_options(${target} PRIVATE ${warnings})
endfunction()
