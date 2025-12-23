file(GLOB PROFILER_SOURCES "src/*.cpp")
file(GLOB_RECURSE PROFILER_HEADERS "src/*.h" "src/*.hpp")

add_library(Profiler SHARED ${PROFILER_SOURCES} ${PROFILER_HEADERS})
target_include_directories(Profiler PUBLIC src)
target_compile_definitions(Profiler PRIVATE
        PROFILER_EXPORTS
        TRACY_ENABLE
        TRACY_EXPORTS
        #    _CRT_SECURE_NO_WARNINGS
)
