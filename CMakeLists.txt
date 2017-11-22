cmake_minimum_required(VERSION 3.5)
project(kit)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align -Wbad-function-cast")
endif ()

#####
# Macro definitions
###
macro(get_subdirectories result current_directory)
    set(directory_list "")
    file(GLOB children RELATIVE ${current_directory} ${current_directory}/*)
    foreach (child ${children})
        if (IS_DIRECTORY ${current_directory}/${child})
            list(APPEND directory_list ${current_directory}/${child})
        endif ()
    endforeach ()
    set(${result} ${directory_list})
endmacro(get_subdirectories)

#####
# Variable definitions
###
set(DEPENDENCIES_PATH ${PROJECT_SOURCE_DIR}/deps)

set(LIBRARY ${PROJECT_NAME})
set(LIBRARY_PATH ${PROJECT_SOURCE_DIR})
file(GLOB LIBRARY_HEADERS ${LIBRARY_PATH}/include/kit/*.h ${LIBRARY_PATH}/include/kit/**/*.h)
file(GLOB LIBRARY_SOURCES ${LIBRARY_PATH}/sources/*.c)

set(SEEDS_LIBRARY "test_seeds")
set(SEEDS_PATH ${PROJECT_SOURCE_DIR}/tests/seeds)
file(GLOB SEEDS_HEADERS ${SEEDS_PATH}/*.h ${SEEDS_PATH}/**/*.h)
file(GLOB SEEDS_SOURCES ${SEEDS_PATH}/*.c ${SEEDS_PATH}/**/*.c)

set(TESTS_PATH "${PROJECT_SOURCE_DIR}/tests")
get_subdirectories(UNIT_TESTS_DIRECTORIES ${TESTS_PATH}/unit)

set(EXAMPLES_PATH ${PROJECT_SOURCE_DIR}/examples)
file(GLOB EXAMPLES_HEADERS ${EXAMPLES_PATH}/*.h)
file(GLOB EXAMPLES_SOURCES ${EXAMPLES_PATH}/*.c)

#####
# Working directories
###
include_directories(include)
include_directories(deps)

#####
# Dependencies
###
include(${DEPENDENCIES_PATH}/traits-unit/traits-unit.cmake)
include(${DEPENDENCIES_PATH}/option/option.cmake)

#####
# Library
###
add_library(${LIBRARY} ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})
target_link_libraries(${LIBRARY} PRIVATE option)

#####
# Seeds
###
# add_library(${SEEDS_LIBRARY} ${SEEDS_HEADERS} ${SEEDS_SOURCES})
# target_link_libraries(${SEEDS_LIBRARY} PRIVATE ${LIBRARY})

#####
# Tests
###
enable_testing()
foreach (path ${UNIT_TESTS_DIRECTORIES})
    file(GLOB test_file ${path}/test_*.c)
    get_filename_component(test_module ${path} NAME_WE)

    set(FIXTURE_LIBRARY "test_${test_module}_fixtures")
    set(FIXTURE_PATH ${path}/fixtures)
    file(GLOB FIXTURE_HEADERS ${FIXTURE_PATH}/fixture_*.h)
    file(GLOB FIXTURE_SOURCES ${FIXTURE_PATH}/fixture_*.c)
    add_library(${FIXTURE_LIBRARY} ${FIXTURE_HEADERS} ${FIXTURE_SOURCES})
    target_link_libraries(${FIXTURE_LIBRARY} PRIVATE ${LIBRARY} ${SEEDS_LIBRARY})
    target_include_directories(${FIXTURE_LIBRARY} PRIVATE ${path} ${SEEDS_PATH})

    set(FEATURE_LIBRARY "test_${test_module}_features")
    set(FEATURE_PATH ${path}/features)
    file(GLOB FEATURE_HEADERS ${FEATURE_PATH}/feature_*.h)
    file(GLOB FEATURE_SOURCES ${FEATURE_PATH}/feature_*.c)
    add_library(${FEATURE_LIBRARY} ${FEATURE_HEADERS} ${FEATURE_SOURCES})
    target_link_libraries(${FEATURE_LIBRARY} PRIVATE ${LIBRARY} ${SEEDS_LIBRARY})
    target_include_directories(${FEATURE_LIBRARY} PRIVATE ${path} ${SEEDS_PATH})

    foreach (source_file ${test_file})
        get_filename_component(target ${source_file} NAME_WE)

        message("module: ")
        message("  name: ${test_module}")
        message("  test:")
        message("    name: ${target}")
        message("    path: ${path}")
        message("    sources: ${source_file}")
        message("    fixture:")
        message("      name: ${FIXTURE_LIBRARY}")
        message("      path: ${FIXTURE_PATH}")
        message("      sources: ${FIXTURE_HEADERS} ${FIXTURE_SOURCES}")
        message("    feature:")
        message("      name: ${FEATURE_LIBRARY}")
        message("      path: ${FEATURE_PATH}")
        message("      sources: ${FEATURE_HEADERS} ${FEATURE_SOURCES}")
        message("\n")

        add_executable(${target} ${source_file} ${TESTS_HEADERS})
        target_link_libraries(${target} PRIVATE ${LIBRARY} ${FIXTURE_LIBRARY} ${FEATURE_LIBRARY} ${SEEDS_LIBRARY} traits-unit)
        add_test(${target} ${target})
    endforeach (source_file)
endforeach (path)

#####
# Examples
###
foreach (source_file ${EXAMPLES_SOURCES})
    get_filename_component(target ${source_file} NAME_WE)
    add_executable(${target} ${source_file})
    target_link_libraries(${target} PRIVATE ${LIBRARY})
endforeach (source_file ${EXAMPLES_SOURCES})
