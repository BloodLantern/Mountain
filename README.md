[![CodeFactor](https://www.codefactor.io/repository/github/bloodlantern/mountain/badge)](https://www.codefactor.io/repository/github/bloodlantern/mountain)
[![MSBuild](https://github.com/BloodLantern/Mountain/actions/workflows/msbuild.yml/badge.svg?branch=master)](https://github.com/BloodLantern/Mountain/actions/workflows/msbuild.yml)

# Mountain

A (currently) Windows-only **C++ Framework for making 2D games**.
It will become available for Linux as well at some point.
This project uses C++23 features.

## Samples

Sample projects are available in the [Samples](https://github.com/BloodLantern/Mountain.Samples) repository.

## Documentation

The Doxygen documentation can be manually generated using the `Doxyfile`.

Most types and functions have documentation in their respective header files, so you can always check them if needed.

## How to use this library

First, you need to have [vcpkg](https://vcpkg.io) installed. See their [get started documentation](https://learn.microsoft.com/en-us/vcpkg/get_started/overview#get-started-with-vcpkg).

Then, you can choose between either using vcpkg or building the framework from source.

### 1. Use the vcpkg package manager

If using manifest mode, run `vcpkg add port mountain`, otherwise run `vcpkg install mountain`.

This is the best way to use the framework as it is available both for CMake and MSBuild projects.

### 2. Build from source

Clone the project using `git clone https://github.com/BloodLantern/Mountain.git`.

Run `cmake -S . -B build`, then `cmake --build build --config Debug` or `cmake --build build --config Release` depending on your preferred configuration.

All the binaries can be found in the `build/bin` folder.
Additionally, copy the `Mountain` directory from `Mountain/src` containing the header files.
As the framework changes, you might also need to get some header files from `build/vcpkg_installed/<your-triplet>/include`.
In its current state, you need all the `ImGui` headers and the `magic_enum` folder, but you might want to take everything just in case.

To then use the framework in any of your projects, do as you would usually: include the necessary headers,
compile by statically linking against the corresponding `Mountain.lib`
(`Debug` or `Release`) and add the related `Mountain.dll` to your executable file directory.

## Profiling

This project uses the [Tracy](https://github.com/wolfpld/tracy) profiler.
To enable profiling of the framework,
set the `MOUNTAIN_OPT_PROFILE` CMake option to `ON`.

## External dependencies used

- [OpenGL](https://www.opengl.org)
- [OpenAL-soft](https://github.com/kcat/openal-soft)
- [FreeType](https://freetype.org)
- [GLAD](https://glad.dav1d.de)
- [ImGui (docking branch)](https://github.com/ocornut/imgui/tree/docking)
- [magic_enum](https://github.com/Neargye/magic_enum)
- [SDL3](https://wiki.libsdl.org/SDL3/FrontPage)
- [minimp3](https://github.com/lieff/minimp3)
- [stb](https://github.com/nothings/stb)
- [MathToolbox](https://github.com/BloodLantern/MathToolbox) (Now merged into this repository)

## Roadmap

- ~~GPU instancing for `Draw` API~~
- ~~`Stopwatch` class from .NET~~
- ~~`TimeSpan` class from .NET~~
- ~~Performance monitoring `ImGui` window~~
- ~~File manager `ImGui` window~~
- ~~Resource manager `ImGui` window~~
- ~~Inputs `ImGui` window~~
- ~~RNG utility function~~
- \[WIP] Particle system
- Separate thread for the rendering
- \[WIP] Custom containers
  - ~~`Array`~~
  - ~~`List`~~
  - `Map`
  - `Stack`
  - `Queue`
  - `LinkedList`
- \[WIP] Common utility functions for all containers
- Thread-safe versions of all custom containers
- \[WIP] Built-in effects to apply on textures
  - ~~Film grain~~
  - ~~Vignette~~
  - ~~Chromatic aberration (both axial and transverse)~~
  - ~~Blur (both box and gaussian)~~
  - Noise
  - ~~Mosaic~~
  - ~~Grayscale~~
  - Color inversion
- ~~Make gamepad input work for both Xbox, PS and Switch controllers~~
- \[WIP] Low-level audio API
- `Audio::Play()` static function
- \[WIP] Low-level graphics API
- ~~`Scene` class~~
- Linux support
- ~~Automatic `std::formatter` implementation for all classes that define a `ToString()` function~~
- ~~Automatic `std::hash` implementation for all classes that define a `GetHashCode()` function~~
- ~~Gamepad rumble support~~
- ~~Gamepad gyro support~~
- ~~`Coroutine` class~~
- ~~Compute shader API~~
- ~~Custom exceptions~~
- Built-in shader hot-reloading
- ~~Real unit tests~~
- ~~Replace all `std::array` and `std::vector` usages with `Mountain::Array` and `Mountain::List`~~
- True text rendering
- ~~Add an instanced Random API to have both a static and instanced way of generating random numbers~~
- Add a way to fade stereo audio buffers from one to another
- ~~Add `DateTime` class from .NET~~
- ~~Replace all `std::chrono` usages by `Stopwatch`, `TimeSpan` and `DateTime`~~
- ~~Credit external dependencies in README~~
- Add a way to use stereo audio files as mono sources and vice-versa
- Add an API to procedurally generate shaders
- Add a tweening system
- ~~Switch to CMake~~
- Publish to vcpkg
