cmake_minimum_required(VERSION 3.16)
project(homework2)

# <Coverage>
set(CMAKE_C_FLAGS "-pedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-pedantic -fprofile-arcs -ftest-coverage")
# </Coverage>

# <Add libraries>
set(TF_IDF_LIB_PATH ${PROJECT_SOURCE_DIR}/tf_idf_lib)

set(tf_idf_cons
        ${TF_IDF_LIB_PATH}/include/read_data.h
        ${TF_IDF_LIB_PATH}/include/hashtable.h
        ${TF_IDF_LIB_PATH}/include/string_val.h
        ${TF_IDF_LIB_PATH}/include/term_freq.h
        ${TF_IDF_LIB_PATH}/source/hashtable.c
        ${TF_IDF_LIB_PATH}/source/read_data.c
        ${TF_IDF_LIB_PATH}/source/string_val.c
        ${TF_IDF_LIB_PATH}/source/term_freq.c)
add_library(tf_idf_cons STATIC ${tf_idf_cons})
target_include_directories(tf_idf_cons PUBLIC ${TF_IDF_LIB_PATH}/include)

set(tf_idf_threads
        ${TF_IDF_LIB_PATH}/include/read_data.h
        ${TF_IDF_LIB_PATH}/include/hashtable.h
        ${TF_IDF_LIB_PATH}/include/string_val.h
        ${TF_IDF_LIB_PATH}/include/term_freq.h
        ${TF_IDF_LIB_PATH}/source_threads/hashtable.c
        ${TF_IDF_LIB_PATH}/source_threads/read_data.c
        ${TF_IDF_LIB_PATH}/source_threads/string_val.c
        ${TF_IDF_LIB_PATH}/source_threads/term_freq.c)
add_library(tf_idf_threads SHARED ${tf_idf_threads})
target_include_directories(tf_idf_threads PUBLIC ${TF_IDF_LIB_PATH}/include)
# </Add libraries>




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
        "${PROJECT_SOURCE_DIR}/tf_idf_lib/source/*.c")
# </Source>

# <SOURCE_DIR>
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
# </SOURCE_DIR>

add_executable(homework2 ${sources})

set_target_properties(homework2 PROPERTIES LINKER_LANGUAGE C)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(homework2 PRIVATE Threads::Threads)

# <Link libraries>
target_link_libraries(${PROJECT_NAME} PRIVATE tf_idf_cons -ldl)
target_link_libraries(${PROJECT_NAME} PRIVATE tf_idf_threads -ldl)
# </Link libraries>