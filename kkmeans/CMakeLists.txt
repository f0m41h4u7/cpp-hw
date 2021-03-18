cmake_minimum_required(VERSION 3.2)

project(kkmeans VERSION 0.0.1)

find_package(dlib REQUIRED)
find_package(OpenBLAS REQUIRED)

add_executable(kkmeans main.cpp)

set_target_properties(kkmeans PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)
target_include_directories(kkmeans
  PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(kkmeans ${CMAKE_THREAD_LIBS_INIT} openblas dlib)

target_link_options(kkmeans PRIVATE -llapacke -llapack -lblas -lrt -lm -lpthread -Wl,--copy-dt-needed-entries)

if (MSVC)
  target_compile_options(kkmeans PRIVATE
      /W4
  )
else ()
  target_compile_options(kkmeans PRIVATE
    -lcblas -Wall -Wextra -pedantic
  )
endif()

install(TARGETS kkmeans RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
