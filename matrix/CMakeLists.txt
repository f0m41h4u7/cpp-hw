cmake_minimum_required(VERSION 3.2)

project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(GTest REQUIRED)
#find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(matrix main.cpp)
add_executable(test test.cpp)

set_target_properties(matrix PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(matrix
    PRIVATE "${CMAKE_BINARY_DIR}"
)

set_target_properties(test PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    #    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    #INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)
target_link_libraries(test GTest::GTest GTest::Main)

if (MSVC)
    target_compile_options(matrix PRIVATE
        /W4
    )
    target_compile_options(test PRIVATE
        /W4
    )
else ()
    target_compile_options(matrix PRIVATE
    )
    target_compile_options(test PRIVATE
    )
endif()

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
