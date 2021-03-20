cmake_minimum_required(VERSION 3.2)

project(realty VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(dlib REQUIRED)
find_package(OpenBLAS REQUIRED)

add_executable(rclst clusterization.cpp)
add_executable(rclss classification.cpp)

set_target_properties(rclst PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)
set_target_properties(rclss PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

target_include_directories(rclst
  PRIVATE "${CMAKE_BINARY_DIR}"
)
target_include_directories(rclss
  PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(rclst ${CMAKE_THREAD_LIBS_INIT} openblas dlib)
target_link_libraries(rclss ${CMAKE_THREAD_LIBS_INIT} openblas dlib)

target_link_options(rclst PRIVATE -lblas -lrt -lm -lpthread -Wl,--copy-dt-needed-entries)
target_link_options(rclss PRIVATE -lblas -lrt -lm -lpthread -Wl,--copy-dt-needed-entries)

if (MSVC)
  target_compile_options(rclst PRIVATE
      /W4
  )
  target_compile_options(rclss PRIVATE
      /W4
  )
else ()
  target_compile_options(rclst PRIVATE
    -lcblas -Wall -Wextra -pedantic
  )
  target_compile_options(rclss PRIVATE
    -lcblas -Wall -Wextra -pedantic
  )
endif()

install(TARGETS rclst RUNTIME DESTINATION bin)
install(TARGETS rclss RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
