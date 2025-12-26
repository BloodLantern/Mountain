set(MOUNTAIN_EXAMPLES_SOURCES
        src/Main.cpp
        src/Scenes/AudioScene.cpp
        src/Scenes/ParticleSystemScene.cpp
        src/Scenes/PostProcessingEffectsScene.cpp
        src/Scenes/ShapesScene.cpp
        src/Scenes/SpriteAnimationsScene.cpp
        src/Scenes/TestScene.cpp
        src/TestGame.cpp
)

set(MOUNTAIN_EXAMPLES_HEADERS
        src/PrecompiledHeader.hpp
        src/Scenes/AudioScene.hpp
        src/Scenes/ParticleSystemScene.hpp
        src/Scenes/PostProcessingEffectsScene.hpp
        src/Scenes/ShapesScene.hpp
        src/Scenes/SpriteAnimationsScene.hpp
        src/Scenes/TestScene.hpp
        src/TestGame.hpp
)

add_executable(Examples ${MOUNTAIN_EXAMPLES_SOURCES} ${MOUNTAIN_EXAMPLES_HEADERS})

target_include_directories(Examples PRIVATE src)

target_link_libraries(Examples PRIVATE Mountain)

# Precompiled headers
target_precompile_headers(Examples PRIVATE src/PrecompiledHeader.hpp)

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
