cmake_minimum_required(VERSION 3.22)
project(kit C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic")

option(KIT_EXPERIMENTAL "Enable experimental features")

set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(INCLUDE_ROOT ${PROJECT_ROOT}/include/kit)
set(SOURCES_ROOT ${PROJECT_ROOT}/src)

set(HEADERS
    ${PROJECT_ROOT}/include/kit.h

    ${INCLUDE_ROOT}/pp.h
    ${INCLUDE_ROOT}/cta.h
    ${INCLUDE_ROOT}/dbg.h
    ${INCLUDE_ROOT}/trace.h
    ${INCLUDE_ROOT}/types.h
    ${INCLUDE_ROOT}/error.h
    ${INCLUDE_ROOT}/require.h
    ${INCLUDE_ROOT}/allocator.h

    ${INCLUDE_ROOT}/memory/layout.h

    ${INCLUDE_ROOT}/alloc/errors.h
    ${INCLUDE_ROOT}/alloc/result.h

    ${INCLUDE_ROOT}/system/allocator.h
   )

set(SOURCES
    ${SOURCES_ROOT}/require.c
    ${SOURCES_ROOT}/allocator.c

    ${SOURCES_ROOT}/alloc/errors.c
    ${SOURCES_ROOT}/alloc/result.c

    ${SOURCES_ROOT}/system/allocator.c
   )

if(KIT_EXPERIMENTAL)
    set(HEADERS
        ${HEADERS}
        ${INCLUDE_ROOT}/__experimental__/allocator/ext.h
        ${INCLUDE_ROOT}/__experimental__/system/allocator/ext.h
       )

    set(SOURCES
        ${SOURCES}
        ${SOURCES_ROOT}/__experimental__/allocator/ext.c
        ${SOURCES_ROOT}/__experimental__/system/allocator/ext.c
       )
endif()

include_directories(${PROJECT_ROOT}/include)

# library
add_library(kit ${HEADERS} ${SOURCES})

# examples
add_executable(person "examples/person.c")
target_link_libraries(person PRIVATE kit)
