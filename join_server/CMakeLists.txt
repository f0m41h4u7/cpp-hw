cmake_minimum_required(VERSION 3.2)

project(join_server VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost 1.54.0 REQUIRED system)
find_package(pegtl)

add_executable(join_server main.cpp)

set_target_properties(join_server PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(join_server
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(join_server ${CMAKE_THREAD_LIBS_INIT} boost_system pthread taocpp::pegtl)

if (MSVC)
    target_compile_options(join_server PRIVATE
        /W4
    )
else ()
    target_compile_options(join_server PRIVATE
      -Wall -Wextra -pedantic
    )
endif()

install(TARGETS join_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
