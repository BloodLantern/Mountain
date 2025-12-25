file(GLOB_RECURSE MOUNTAIN_EXAMPLES_SOURCES "src/*.cpp")
file(GLOB_RECURSE MOUNTAIN_EXAMPLES_HEADERS "src/*.hpp")

add_executable(Examples ${MOUNTAIN_EXAMPLES_SOURCES} ${MOUNTAIN_EXAMPLES_HEADERS})

target_include_directories(Examples PRIVATE src)

target_link_libraries(Examples PRIVATE Mountain)

# Precompiled headers
target_precompile_headers(Examples PRIVATE src/Common.hpp)

# Copy shaders and assets to output directory
add_custom_command(
        TARGET Examples POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Mountain/shaders_internal
        $<TARGET_FILE_DIR:Examples>/shaders_internal
)
add_custom_command(
        TARGET Examples POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Mountain/assets_internal
        $<TARGET_FILE_DIR:Examples>/assets_internal
)

add_custom_command(
        TARGET Examples POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Examples/assets
        $<TARGET_FILE_DIR:Examples>/assets
)

set_target_properties(
        Examples
        PROPERTIES DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:Examples>
)
