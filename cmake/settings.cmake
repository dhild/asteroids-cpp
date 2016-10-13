macro(config_compiler_and_linker)
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(cxx_base_flags "-std=gnu++11 -Wall -Wshadow")
        set(cxx_exception_flags "-fexceptions")
        set(cxx_strict_flags
                "-Werror -Wextra -Wno-unused-parameter -Wno-missing-field-initializers")
    endif()

    set(cxx_exception "${CMAKE_CXX_FLAGS} ${cxx_base_flags} ${cxx_exception_flags}")
    set(cxx_default "${cxx_exception}")

    set(cxx_flags "${cxx_default} ${cxx_strict_flags}")
endmacro()

function(cxx_library name)
    add_library(${name} ${type} ${ARGN})
    set_target_properties(${name}
            PROPERTIES
            COMPILE_FLAGS "${cxx_flags}")
endfunction()

function(cxx_executable name libs)
    add_executable(${name} ${ARGN})
    set_target_properties(${name}
            PROPERTIES
            COMPILE_FLAGS "${cxx_flags}")
    # To support mixing linking in static and dynamic libraries, link each
    # library in with an extra call to target_link_libraries.
    foreach (lib "${libs}")
        target_link_libraries(${name} ${lib})
    endforeach()
endfunction()

function(cxx_test name libs)
    cxx_executable(${name} "${libs}" ${ARGN})
    target_link_libraries(${name} gtest)
    target_link_libraries(${name} gtest_main)
    add_test(${name} ${name})
endfunction()
