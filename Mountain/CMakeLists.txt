# Mountain library
set(MOUNTAIN_SOURCES
        src/Mountain/Audio/Audio.cpp
        src/Mountain/Audio/AudioBuffer.cpp
        src/Mountain/Audio/AudioContext.cpp
        src/Mountain/Audio/AudioDevice.cpp
        src/Mountain/BinaryResources/resource_holder.cpp
        src/Mountain/Collision/Circle.cpp
        src/Mountain/Collision/Collider.cpp
        src/Mountain/Collision/ColliderList.cpp
        src/Mountain/Collision/Collision.cpp
        src/Mountain/Collision/Grid.cpp
        src/Mountain/Collision/Hitbox.cpp
        src/Mountain/Ecs/Component/AudioListener.cpp
        src/Mountain/Ecs/Component/AudioSource.cpp
        src/Mountain/Ecs/Component/Component.cpp
        src/Mountain/Ecs/Component/Sprite.cpp
        src/Mountain/Ecs/Entity.cpp
        src/Mountain/Ecs/Scene.cpp
        src/Mountain/Exceptions/ArgumentException.cpp
        src/Mountain/Exceptions/Exception.cpp
        src/Mountain/FileSystem/Directory.cpp
        src/Mountain/FileSystem/Entry.cpp
        src/Mountain/FileSystem/File.cpp
        src/Mountain/FileSystem/FileManager.cpp
        src/Mountain/Game.cpp
        src/Mountain/Graphics/Draw.cpp
        src/Mountain/Graphics/Effect.cpp
        src/Mountain/Graphics/GpuBuffer.cpp
        src/Mountain/Graphics/GpuFramebuffer.cpp
        src/Mountain/Graphics/GpuTexture.cpp
        src/Mountain/Graphics/GpuVertexArray.cpp
        src/Mountain/Graphics/Graphics.cpp
        src/Mountain/Graphics/ParticleSystem.cpp
        src/Mountain/Graphics/ParticleSystemModules.cpp
        src/Mountain/Graphics/Renderer.cpp
        src/Mountain/Graphics/RenderTarget.cpp
        src/Mountain/Input/GamepadInput.cpp
        src/Mountain/Input/Input.cpp
        src/Mountain/Input/Time.cpp
        src/Mountain/Math/Calc.cpp
        src/Mountain/Math/Easing.cpp
        src/Mountain/Math/Matrix.cpp
        src/Mountain/Math/Matrix2.cpp
        src/Mountain/Math/Matrix3.cpp
        src/Mountain/Math/Quaternion.cpp
        src/Mountain/Math/Vector2.cpp
        src/Mountain/Math/Vector2i.cpp
        src/Mountain/Math/Vector3.cpp
        src/Mountain/Math/Vector4.cpp
        src/Mountain/Platform/Windows/Windows.cpp
        src/Mountain/Platform/Linux/Linux.cpp
        src/Mountain/Platform/Platform.cpp
        src/Mountain/Resource/AudioTrack.cpp
        src/Mountain/Resource/ComputeShader.cpp
        src/Mountain/Resource/Font.cpp
        src/Mountain/Resource/Resource.cpp
        src/Mountain/Resource/ResourceManager.cpp
        src/Mountain/Resource/Shader.cpp
        src/Mountain/Resource/ShaderBase.cpp
        src/Mountain/Resource/Texture.cpp
        src/Mountain/Screen.cpp
        src/Mountain/Utils/Color.cpp
        src/Mountain/Utils/Coroutine.cpp
        src/Mountain/Utils/DateTime.cpp
        src/Mountain/Utils/FileSystemWatcher.cpp
        src/Mountain/Utils/Guid.cpp
        src/Mountain/Utils/ImGuiUtils.cpp
        src/Mountain/Utils/Logger.cpp
        src/Mountain/Utils/MessageBox.cpp
        src/Mountain/Utils/Random.cpp
        src/Mountain/Utils/Stopwatch.cpp
        src/Mountain/Utils/TimeSpan.cpp
        src/Mountain/Utils/Utils.cpp
        src/Mountain/Window.cpp
        src/Mountain/Utils/Version.cpp
)

set(MOUNTAIN_HEADERS
        src/Mountain/Attributes.hpp
        src/Mountain/Audio/Audio.hpp
        src/Mountain/Audio/AudioBuffer.hpp
        src/Mountain/Audio/AudioContext.hpp
        src/Mountain/Audio/AudioDevice.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_10604039599264331763.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_10671969735137121559.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_11431338934652808651.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_11774202807359543870.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_11952871429675989627.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_12442680368039291515.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_1291378986966553985.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_13070826838953012323.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_13177006652388307822.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_14338357782030755284.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_14381367057370009788.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_1453103019202383270.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_15258004472844539140.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_15961880810884371948.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_16126662360900569018.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_16222346625001150542.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_16311089013737800627.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_16451689749247673836.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_1659229443278887099.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_1682259173912325418.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_17150819399866535910.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_17163117651341958810.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_17404448839198764618.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_17495974214214295230.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_17880426697011385839.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_18011218881129316092.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_310597202658876699.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_3126981312599726777.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_332208238769912247.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_4319606583867259020.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_5284316122615694636.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_5513601353699197311.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_6180361286818081308.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_6423258116736183732.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_6733528840531529029.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_6826460111274356971.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_6975910120903775418.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_7369051294668265954.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_7556603881106790027.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_7736256087137476443.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_8867495104694417582.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_908422867440665036.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_9162261963507646339.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_9225507554395683774.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_9508759643910089710.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_9550955058371070276.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_9582143994837232440.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_9699825830242037512.hpp
        src/Mountain/BinaryResources/embedded_resources/resource_9926314955806432672.hpp
        src/Mountain/BinaryResources/resource.hpp
        src/Mountain/BinaryResources/resource_holder.hpp
        src/Mountain/BinaryResources/span.hpp
        src/Mountain/Collision/Circle.hpp
        src/Mountain/Collision/Collider.hpp
        src/Mountain/Collision/ColliderList.hpp
        src/Mountain/Collision/Collision.hpp
        src/Mountain/Collision/Grid.hpp
        src/Mountain/Collision/Hitbox.hpp
        src/Mountain/CompilerSpecific.hpp
        src/Mountain/Configuration.hpp
        src/Mountain/Containers/Array.hpp
        src/Mountain/Containers/ContiguousIterator.hpp
        src/Mountain/Containers/EnumerableExt.hpp
        src/Mountain/Containers/FunctionTypes.hpp
        src/Mountain/Containers/List.hpp
        src/Mountain/Core.hpp
        src/Mountain/Ecs/Component/AudioListener.hpp
        src/Mountain/Ecs/Component/AudioSource.hpp
        src/Mountain/Ecs/Component/Component.hpp
        src/Mountain/Ecs/Component/Sprite.hpp
        src/Mountain/Ecs/Component/StateMachine.hpp
        src/Mountain/Ecs/Entity.hpp
        src/Mountain/Ecs/EntityList.hpp
        src/Mountain/Ecs/Scene.hpp
        src/Mountain/Exceptions/ArgumentException.hpp
        src/Mountain/Exceptions/Exception.hpp
        src/Mountain/Exceptions/ThrowHelper.hpp
        src/Mountain/FileSystem/Directory.hpp
        src/Mountain/FileSystem/Entry.hpp
        src/Mountain/FileSystem/File.hpp
        src/Mountain/FileSystem/FileManager.hpp
        src/Mountain/Game.hpp
        src/Mountain/Globals.hpp
        src/Mountain/Graphics/Draw.hpp
        src/Mountain/Graphics/Effect.hpp
        src/Mountain/Graphics/GpuBuffer.hpp
        src/Mountain/Graphics/GpuFramebuffer.hpp
        src/Mountain/Graphics/GpuTexture.hpp
        src/Mountain/Graphics/GpuVertexArray.hpp
        src/Mountain/Graphics/Graphics.hpp
        src/Mountain/Graphics/LightSource.hpp
        src/Mountain/Graphics/ParticleSystem.hpp
        src/Mountain/Graphics/ParticleSystemModules.hpp
        src/Mountain/Graphics/Renderer.hpp
        src/Mountain/Graphics/RenderTarget.hpp
        src/Mountain/Input/GamepadInput.hpp
        src/Mountain/Input/Input.hpp
        src/Mountain/Input/KeyboardInput.hpp
        src/Mountain/Input/MouseInput.hpp
        src/Mountain/Input/Time.hpp
        src/Mountain/Math/Calc.hpp
        src/Mountain/Math/Easing.hpp
        src/Mountain/Math/Math.hpp
        src/Mountain/Math/Matrix.hpp
        src/Mountain/Math/Matrix2.hpp
        src/Mountain/Math/Matrix3.hpp
        src/Mountain/Math/Quaternion.hpp
        src/Mountain/Math/Vector2.hpp
        src/Mountain/Math/Vector2i.hpp
        src/Mountain/Math/Vector3.hpp
        src/Mountain/Math/Vector4.hpp
        src/Mountain/Platform/Windows/Windows.hpp
        src/Mountain/Platform/Linux/Linux.hpp
        src/Mountain/Platform/Platform.hpp
        src/Mountain/Mountain.hpp
        src/Mountain/PrecompiledHeader.hpp
        src/Mountain/Profiler.hpp
        src/Mountain/Resource/AudioTrack.hpp
        src/Mountain/Resource/ComputeShader.hpp
        src/Mountain/Resource/Font.hpp
        src/Mountain/Resource/Resource.hpp
        src/Mountain/Resource/ResourceManager.hpp
        src/Mountain/Resource/Shader.hpp
        src/Mountain/Resource/ShaderBase.hpp
        src/Mountain/Resource/Texture.hpp
        src/Mountain/Screen.hpp
        src/Mountain/Utils/Color.hpp
        src/Mountain/Utils/Coroutine.hpp
        src/Mountain/Utils/DateTime.hpp
        src/Mountain/Utils/Event.hpp
        src/Mountain/Utils/FileSystemWatcher.hpp
        src/Mountain/Utils/Formatter.hpp
        src/Mountain/Utils/Guid.hpp
        src/Mountain/Utils/ImGuiUtils.hpp
        src/Mountain/Utils/Logger.hpp
        src/Mountain/Utils/MessageBox.hpp
        src/Mountain/Utils/MetaProgramming.hpp
        src/Mountain/Utils/Optional.hpp
        src/Mountain/Utils/Pointer.hpp
        src/Mountain/Utils/Random.hpp
        src/Mountain/Utils/Rectangle.hpp
        src/Mountain/Utils/ReferenceCounter.hpp
        src/Mountain/Utils/Requirements.hpp
        src/Mountain/Utils/Stopwatch.hpp
        src/Mountain/Utils/TimeSpan.hpp
        src/Mountain/Utils/TsQueue.hpp
        src/Mountain/Utils/Utils.hpp
        src/Mountain/Window.hpp
        src/Mountain/Utils/Version.hpp
)

set(MOUNTAIN_EXTERNALS_SOURCES
        externals/src/glad.c
        externals/src/minimp3.c
        externals/src/stb_image.c
        externals/src/stb_vorbis_impl.c
)

set(MOUNTAIN_EXTERNALS_HEADERS
        externals/src/glad/glad.h
        externals/src/KHR/khrplatform.h
        externals/src/minimp3.h
        externals/src/minimp3_ex.h
        externals/src/stb_vorbis.h
        src/Mountain/ImGuiConfig.hpp
)

add_library(Mountain SHARED
        ${MOUNTAIN_SOURCES}
        ${MOUNTAIN_HEADERS}
        ${MOUNTAIN_EXTERNALS_SOURCES}
        ${MOUNTAIN_EXTERNALS_HEADERS}
)
add_library(${EXPORT_NAMESPACE}Mountain ALIAS Mountain)

target_include_directories(Mountain PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>   # for headers when building
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/externals/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>  # for client in install mode
)

target_include_directories(Mountain PRIVATE
        ${Stb_INCLUDE_DIR}
        ${MINIMP3_INCLUDE_DIRS}
)

target_link_libraries(Mountain PUBLIC
        magic_enum::magic_enum
        imgui::imgui
)

target_link_libraries(Mountain PRIVATE
        Freetype::Freetype
        SDL3::SDL3
        OpenGL::GL
        OpenAL::OpenAL
)

target_compile_definitions(Mountain PUBLIC
        MATH_DEFINE_FORMATTER
        MOUNTAIN_VERSION=${MOUNTAIN_VERSION}
)

target_compile_definitions(Mountain PRIVATE
        MOUNTAIN_EXPORT
        IMGUI_EXPORT
        RAPID_XML_EXPORT
        AL_ALEXT_PROTOTYPES
)

if (MOUNTAIN_OPT_PROFILE)
    target_compile_definitions(Mountain PUBLIC MOUNTAIN_USE_PROFILER)
    target_link_libraries(Mountain PUBLIC Profiler)
endif ()

# Precompiled headers
target_precompile_headers(Mountain PRIVATE src/Mountain/PrecompiledHeader.hpp)

set_source_files_properties(${MOUNTAIN_EXTERNALS_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_link_options(Mountain PRIVATE
            /NATVIS:${CMAKE_CURRENT_LIST_DIR}/Mountain.natvis
    )
endif ()

if (MOUNTAIN_OPT_INSTALL)
    include(CMakePackageConfigHelpers)

    # Install the library and its headers
    install(TARGETS Mountain
            EXPORT Mountain_Targets
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
            FILES_MATCHING PATTERN "*.hpp"
    )

    # Generate and install *-targets.cmake
    install(EXPORT Mountain_Targets
            FILE MountainTargets.cmake
            NAMESPACE ${EXPORT_NAMESPACE}
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Mountain"
    )

    # Generate *Config.cmake and *ConfigVersion.cmake
    write_basic_package_version_file(
            "MountainConfigVersion.cmake"
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY SameMajorVersion
    )

    configure_package_config_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/MountainConfig.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/MountainConfig.cmake"
            INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Mountain"
    )

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/MountainConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/MountainConfigVersion.cmake"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Mountain"
    )
endif ()
