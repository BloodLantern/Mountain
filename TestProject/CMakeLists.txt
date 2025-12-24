file(GLOB_RECURSE TEST_PROJECT_SOURCES "src/*.cpp")
file(GLOB_RECURSE TEST_PROJECT_HEADERS "src/*.hpp")

add_executable(TestProject ${TEST_PROJECT_SOURCES} ${TEST_PROJECT_HEADERS})

target_include_directories(TestProject PRIVATE src)

target_link_libraries(TestProject PRIVATE
    Mountain
    Profiler
)

# Precompiled headers
target_precompile_headers(TestProject PRIVATE src/Common.hpp)

# Copy shaders and assets to output directory
add_custom_command(TARGET TestProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Mountain/shaders_internal
        $<TARGET_FILE_DIR:TestProject>/shaders_internal
)

add_custom_command(TARGET TestProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/TestProject/assets
        $<TARGET_FILE_DIR:TestProject>/assets
)
