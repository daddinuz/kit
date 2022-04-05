cmake_minimum_required(VERSION 3.22)
project(kit C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic")

set(BASE ${CMAKE_CURRENT_LIST_DIR})

set(HEADERS
    ${BASE}/include/kit.h
    ${BASE}/include/kit/cta.h
    ${BASE}/include/kit/trace.h
    ${BASE}/include/kit/dbg.h
    ${BASE}/include/kit/memory/layout.h
    ${BASE}/include/kit/allocator.h
    ${BASE}/include/kit/pp.h
    ${BASE}/include/kit/types.h
    ${BASE}/include/kit/require.h
    ${BASE}/include/kit/error.h
   )

set(SOURCES
    ${BASE}/src/allocator/system.c
    ${BASE}/src/allocator.c
    ${BASE}/src/require.c
   )

include_directories(include)

# library
add_library(kit ${HEADERS} ${SOURCES})

# examples
add_executable(person "examples/person.c")
target_link_libraries(person PRIVATE kit)
