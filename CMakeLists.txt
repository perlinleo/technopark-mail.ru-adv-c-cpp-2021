cmake_minimum_required(VERSION 3.16)
project(homework2)

# <Coverage>
set(CMAKE_C_FLAGS "-pedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-pedantic -fprofile-arcs -ftest-coverage")
# </Coverage>

# <Test>
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
      ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(test)
# </Test>

# <Source>
set(CMAKE_BUILD_TYPE Debug)
include_directories("${PROJECT_SOURCE_DIR}/tf_idf_lib/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/tf_idf_lib/include/*.h"
        "${PROJECT_SOURCE_DIR}/tf_idf_lib/source*.c")
# </Source>

# <SOURCE_DIR>
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
# </SOURCE_DIR>

add_executable(homework2 ${sources})

set_target_properties(homework2 PROPERTIES LINKER_LANGUAGE C)