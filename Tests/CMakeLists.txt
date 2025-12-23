file(GLOB_RECURSE TESTS_SOURCES "src/*.cpp")
file(GLOB_RECURSE TESTS_HEADERS "src/*.hpp")

add_executable(MountainTests ${TESTS_SOURCES} ${TESTS_HEADERS})

target_include_directories(MountainTests PRIVATE src)

target_link_libraries(MountainTests PRIVATE
    Mountain
    Profiler
)

# Precompiled headers
target_precompile_headers(MountainTests PRIVATE src/Common.hpp)

# Copy shaders and assets to output directory
add_custom_command(TARGET MountainTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Mountain/shaders_internal
        $<TARGET_FILE_DIR:MountainTests>/shaders_internal
)

add_custom_command(TARGET MountainTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Tests/assets
        $<TARGET_FILE_DIR:MountainTests>/assets
)
