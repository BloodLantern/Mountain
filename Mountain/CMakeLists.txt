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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>   # for headers when building
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/externals/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>  # for client in install mode
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${Stb_INCLUDE_DIR}
        ${MINIMP3_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        magic_enum::magic_enum
        imgui::imgui
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Freetype::Freetype
        SDL3::SDL3
        OpenGL::GL
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

if (MOUNTAIN_OPT_INSTALL)
    include(CMakePackageConfigHelpers)

    # Install the library and its headers
    install(TARGETS ${PROJECT_NAME}
            EXPORT ${PROJECT_NAME}_Targets
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
            FILES_MATCHING PATTERN "*.hpp"
    )

    # Generate and install *-targets.cmake
    install(EXPORT ${PROJECT_NAME}_Targets
            FILE ${PROJECT_NAME}Targets.cmake
            NAMESPACE ${EXPORT_NAMESPACE}
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
    )

    # Generate *Config.cmake and *ConfigVersion.cmake
    write_basic_package_version_file(
            "${PROJECT_NAME}ConfigVersion.cmake"
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY SameMajorVersion
    )

    configure_package_config_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
            INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
    )

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
    )
endif ()
