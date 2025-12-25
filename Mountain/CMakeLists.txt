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

add_library(${PROJECT_NAME} SHARED
        ${MOUNTAIN_SOURCES}
        ${MOUNTAIN_HEADERS}
        ${MOUNTAIN_EXTERNALS_SOURCES}
        ${MOUNTAIN_EXTERNALS_HEADERS}
)
add_library(${EXPORT_NAMESPACE}${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

target_include_directories(${PROJECT_NAME} PUBLIC
        src
        externals/src
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        magic_enum::magic_enum
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        freetype
        SDL3::SDL3
        opengl32.lib
        OpenAL::OpenAL
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
        MATH_DEFINE_FORMATTER
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        MOUNTAIN_EXPORT
        IMGUI_EXPORT
        RAPID_XML_EXPORT
        AL_ALEXT_PROTOTYPES
)

if (MOUNTAIN_OPT_PROFILE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC MOUNTAIN_USE_PROFILER)
    target_link_libraries(${PROJECT_NAME} PUBLIC Profiler)
endif ()

# Precompiled headers
target_precompile_headers(${PROJECT_NAME} PRIVATE src/Mountain/PrecompiledHeader.hpp)

set_source_files_properties(${MOUNTAIN_EXTERNALS_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_link_options(${PROJECT_NAME} PRIVATE
            /NATVIS:${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.natvis
    )
endif ()
