cmake_minimum_required(VERSION 3.9)

project(async VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Threads REQUIRED)
find_package(Boost 1.54.0 REQUIRED system)

add_library(async SHARED
  async.hpp
  handler.cpp
  handler.hpp
)

add_executable(main main.cpp)

set_target_properties(async PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  PUBLIC_HEADER async.hpp
)

set_target_properties(main PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)

target_include_directories(async
  PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(async
	${CMAKE_THREAD_LIBS_INIT} boost_system pthread
)

target_include_directories(main
  PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(main PRIVATE
  async
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -lboost_coroutine -fcoroutines")

if (MSVC)
  target_compile_options(async PRIVATE
    /W4
  )
  target_compile_options(main PRIVATE
    /W4
  )
else ()
  target_compile_options(async PRIVATE
    -Wall -Wextra -pedantic -Wl,--no-as-needed -lpthread
  )
  target_compile_options(main PRIVATE
    -Wall -Wextra -pedantic -Wl,--no-as-needed -lpthread
  )
endif()

include(GNUInstallDirs)
install(
  TARGETS async
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS main RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
