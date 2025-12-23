# Mountain library
file(GLOB_RECURSE MOUNTAIN_SOURCES "src/Mountain/*.cpp")
file(GLOB_RECURSE MOUNTAIN_HEADERS "src/Mountain/*.hpp")
file(GLOB_RECURSE MOUNTAIN_EXTERNALS_SOURCES
        "externals/src/*.c"
        "externals/src/*.cpp"
)
file(GLOB_RECURSE MOUNTAIN_EXTERNALS_HEADERS
        "externals/src/*.h"
        "externals/src/*.hpp"
)

add_library(Mountain SHARED
        ${MOUNTAIN_SOURCES}
        ${MOUNTAIN_HEADERS}
        ${MOUNTAIN_EXTERNALS_SOURCES}
        ${MOUNTAIN_EXTERNALS_HEADERS}
)

target_include_directories(Mountain PUBLIC
        src
        externals/src
)

target_link_libraries(Mountain PRIVATE
        freetype
        SDL3::SDL3
        magic_enum::magic_enum
        opengl32.lib
        OpenAL32.lib
        soft_oal.lib
)

# OpenAL dependencies - assuming they might be in externals/libs or found via vcpkg
# The vcpkg.json doesn't list openal, but the vcxproj had OpenAL32.lib.
# Let's check if it's in externals/libs/static
target_link_directories(Mountain PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/externals/libs/static/Debug
        ${CMAKE_CURRENT_SOURCE_DIR}/externals/libs/static/Common
)

target_compile_definitions(Mountain PRIVATE
        MOUNTAIN_EXPORT
        MATH_EXPORT
        MATH_DEFINE_FORMATTER
        IMGUI_EXPORT
        RAPID_XML_EXPORT
        AL_ALEXT_PROTOTYPES
)

# Precompiled headers
target_precompile_headers(Mountain PRIVATE src/Mountain/PrecompiledHeader.hpp)

set_source_files_properties(${MOUNTAIN_EXTERNALS_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
