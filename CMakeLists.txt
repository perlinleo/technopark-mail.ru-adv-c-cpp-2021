cmake_minimum_required(VERSION 3.16)
project(individual-task1)

# <Coverage>

# </Coverage>

# <Test>

# </Test>

# <Source>
include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c")
# </Source>

# <SOURCE_DIR>
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
# </SOURCE_DIR>

add_executable(individual-task1 ${sources})