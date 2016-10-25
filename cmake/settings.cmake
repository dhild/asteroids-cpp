macro(config_compiler_and_linker)
    if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(cxx_base_flags "-Wall -Wshadow -fexceptions")
        set(cxx_strict_flags "-Werror -Wextra -Wno-unused-parameter -Wno-missing-field-initializers")
        set(cxx_strict_flags "${cxx_strict_flags} -Wreturn-type")
        set(cxx_strict_flags "${cxx_strict_flags} -Wcast-align")
        set(cxx_strict_flags "${cxx_strict_flags} -Wshadow")
        set(cxx_strict_flags "${cxx_strict_flags} -Wno-unused-parameter")
        set(cxx_strict_flags "${cxx_strict_flags} -Wno-missing-field-initializers")
        set(cxx_strict_flags "${cxx_strict_flags} -fno-strict-aliasing")
        set(cxx_strict_flags "${cxx_strict_flags} -fno-builtin-memcmp")
        if (UNIX)
            set(cxx_base_flags "${cxx_base_flags} -fvisibility=hidden")
        endif ()
    endif()
    set(cxx_default "${CMAKE_CXX_FLAGS} ${cxx_base_flags}")

    set(cxx_flags "${cxx_default} ${cxx_strict_flags}")
endmacro()

function(cxx_library name)
    add_library(${name} ${type} ${ARGN})
    set_target_properties(${name}
            PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON
            COMPILE_FLAGS "${cxx_flags}")
endfunction()

function(cxx_executable name libs)
    add_executable(${name} ${ARGN})
    set_target_properties(${name}
            PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON
            COMPILE_FLAGS "${cxx_flags}")
    # To support mixing linking in static and dynamic libraries, link each
    # library in with an extra call to target_link_libraries.
    foreach (lib "${libs}")
        target_link_libraries(${name} ${lib})
    endforeach()
endfunction()

function(cxx_test name libs)
    cxx_executable(${name} "${libs}" "${name}.cpp" ${ARGN})
    set_target_properties(${name}
            PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON
            COMPILE_FLAGS "${cxx_flags}")
    target_link_libraries(${name} gtest)
    target_link_libraries(${name} gtest_main)
    add_test(${name} ${name})
endfunction()


function(find_font_file outputvar)
    execute_process(
            COMMAND fc-match --format=%{file} LiberationMono-Regular.ttf
            OUTPUT_VARIABLE ${outputvar})
endfunction()
