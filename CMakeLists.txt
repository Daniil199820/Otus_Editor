cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(simple_editor VERSION ${PROJECT_VERSION})

add_executable(simple_editor main.cpp)
add_library(lib_editor lib_editor.cpp)

set_target_properties(simple_editor lib_editor PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(simple_editor PRIVATE
    lib_editor
)

if (MSVC)

    target_compile_options(simple_editor PRIVATE
        /W4
    )
    target_compile_options(lib_editor PRIVATE
        /W4
    )
else ()
    target_compile_options(simple_editor PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lib_editor PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS editor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)