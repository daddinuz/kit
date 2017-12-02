get_filename_component(ARCHIVE_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)
message("${ARCHIVE_NAME}@${CMAKE_CURRENT_LIST_DIR} using: ${CMAKE_CURRENT_LIST_FILE} ")

file(GLOB HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/*.h")
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/*.c")
add_library("${ARCHIVE_NAME}" "${HEADER_FILES}" "${SOURCE_FILES}")
target_link_libraries("${ARCHIVE_NAME}" PRIVATE option)
