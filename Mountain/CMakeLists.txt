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

set_target_properties(Mountain PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

target_include_directories(Mountain PUBLIC
        src
        externals/src
)

target_link_libraries(Mountain PUBLIC
        magic_enum::magic_enum
)

target_link_libraries(Mountain PRIVATE
        freetype
        SDL3::SDL3
        opengl32.lib
        OpenAL::OpenAL
)

target_compile_definitions(Mountain PUBLIC
        MATH_DEFINE_FORMATTER
)

target_compile_definitions(Mountain PRIVATE
        MOUNTAIN_EXPORT
        IMGUI_EXPORT
        RAPID_XML_EXPORT
        AL_ALEXT_PROTOTYPES
)

# Precompiled headers
target_precompile_headers(Mountain PRIVATE src/Mountain/PrecompiledHeader.hpp)

set_source_files_properties(${MOUNTAIN_EXTERNALS_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
