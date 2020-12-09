cmake_minimum_required(VERSION 3.2)

project(editor VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(editor main.cpp)

set_target_properties(editor PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(editor
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(editor PRIVATE
        /W4
    )
else ()
    target_compile_options(editor PRIVATE
        -Wall -Wextra -pedantic 
    )
endif()

install(TARGETS editor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
