cmake_minimum_required(VERSION 3.22)
project(kit C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic")

set(BASE ${CMAKE_CURRENT_LIST_DIR})

set(HEADERS
    ${BASE}/include/kit.h

    ${BASE}/include/kit/pp.h
    ${BASE}/include/kit/cta.h
    ${BASE}/include/kit/dbg.h
    ${BASE}/include/kit/trace.h
    ${BASE}/include/kit/types.h
    ${BASE}/include/kit/error.h
    ${BASE}/include/kit/require.h
    ${BASE}/include/kit/allocator.h

    ${BASE}/include/kit/memory/layout.h

    ${BASE}/include/kit/alloc/errors.h
    ${BASE}/include/kit/alloc/result.h

    ${BASE}/include/kit/system/allocator.h
   )

set(SOURCES
    ${BASE}/src/require.c
    ${BASE}/src/allocator.c

    ${BASE}/src/alloc/errors.c
    ${BASE}/src/alloc/result.c

    ${BASE}/src/system/allocator.c
   )

include_directories(include)

# library
add_library(kit ${HEADERS} ${SOURCES})

# examples
add_executable(person "examples/person.c")
target_link_libraries(person PRIVATE kit)
