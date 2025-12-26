set(MOUNTAIN_PROFILER_SOURCES
        "src/Profiler.cpp"
        "src/TracyClient.cpp"
)
set(MOUNTAIN_PROFILER_HEADERS
        "src/Profiler.hpp"
)

add_library(Profiler SHARED ${MOUNTAIN_PROFILER_SOURCES} ${MOUNTAIN_PROFILER_HEADERS})

target_include_directories(Profiler PUBLIC src)

target_compile_definitions(Profiler PRIVATE
        PROFILER_EXPORTS
        TRACY_ENABLE
        TRACY_EXPORTS
        WINVER=0x0602 # Needed to build with MinGW for some reason
)
