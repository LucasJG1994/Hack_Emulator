# CMakeLists files in this project can
# refer to the root source directory of the project as ${hackemu_SOURCE_DIR} and
# to the root binary directory of the project as ${hackemu_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (hackemu)

# Recurse into the "lib/minifb". This does not actually cause another cmake executable to run. The same process will
# walk through the project's entire directory structure.
add_subdirectory (lib/minifb)

# Bring the headers for MiniFB into the project
include_directories(
        lib/minifb/include
)

add_executable (hackemu
        ${hackemu_SOURCE_DIR}/src/byte.c
)

target_link_libraries(hackemu minifb)
