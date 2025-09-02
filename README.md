[![CodeFactor](https://www.codefactor.io/repository/github/bloodlantern/mountain/badge)](https://www.codefactor.io/repository/github/bloodlantern/mountain)
[![Build](https://github.com/BloodLantern/Mountain/actions/workflows/msbuild.yml/badge.svg?branch=master)](https://github.com/BloodLantern/Mountain/actions/workflows/msbuild.yml)

# Mountain

A (currently) Windows-only **C++ Framework for making 2D games**.
It will become available for Linux as well at some point.

## Language version and architecture

This project is compiled using C++23 features (`/std:c++latest`), on MSVC, for the `x64` architecture.
Also, it uses some very recent features from the Windows API (as recent as September 2023), so if the code doesn't compile, make sure to update to the latest Visual Studio version.

## Samples

Sample projects are available in the [Samples](https://github.com/BloodLantern/Mountain.Samples) repository.

## Documentation

The Doxygen documentation can be manually generated using the `Doxyfile`.

Most types and functions have documentation in their respective header files, so you can always check them if needed.

## How to use this library

You can choose between two ways of using this framework for your projects.

Both require to have [vcpkg](https://vcpkg.io) installed.

### 1. Use this as a submodule (recommended)

In a directory of your choice within your project, run `git submodule add --recurse-submodules https://github.com/BloodLantern/Mountain.git`.

Add the `Mountain/Mountain.vcxproj` project to your solution and set it as a reference to your project using `Add > Reference...`.
In your project configuration, add the `Mountain/src`, `Mountain/externals/src` and `MathToolbox/src` folders to your include path.

### 2. Build from source

Clone the project using `git clone https://github.com/BloodLantern/Mountain.git`.
Open the Visual Studio solution file found in the root directory.
After opening it, the only thing you have to do is to build the framework (Mountain project) in both the`Debug` and `Release` configuration.

All the binaries can be found in the `x64/(Debug|Release)` folder.
Additionally, copy the header files from `Mountain/src`.
As the framework changes, you might also need to get some header files from `Mountain/externals/src`.
In its current state, you need the `ImGui` and `magic_enum` folders, but you might want to take everything just in case.
You also need the math headers, which are located in `MathToolbox/src`.

To then use the framework in any of your projects, do as you would usually: include the necessary headers,
compile by statically linking against the corresponding `Mountain.lib`
(`Debug` or `Release`) and add the correct `Mountain.dll` to your executable file directory.

## External dependencies used

- [OpenGL](https://www.opengl.org)
- [OpenAL](https://github.com/kcat/openal-soft)
- [FreeType](https://freetype.org)
- [GLAD](https://glad.dav1d.de)
- [ImGui (docking branch)](https://github.com/ocornut/imgui/tree/docking)
- [magic_enum](https://github.com/Neargye/magic_enum)
- [mimalloc](https://github.com/microsoft/mimalloc)
- [RapidXML](https://rapidxml.sourceforge.net/)
- [SDL3](https://wiki.libsdl.org/SDL3/FrontPage)
- [minimp3](https://github.com/lieff/minimp3)
- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
- [stb_vorbis](https://github.com/nothings/stb/blob/master/stb_vorbis.h)
- [MathToolbox](https://github.com/BloodLantern/MathToolbox) (Submodule)

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
- \[WIP] Real unit tests
- ~~Replace all `std::array` and `std::vector` usages with `Mountain::Array` and `Mountain::List`~~
- True text rendering
- ~~Add an instanced Random API to have both a static and instanced way of generating random numbers~~
- Add a way to fade stereo audio buffers from one to another
- ~~Add `DateTime` class from .NET~~
- ~~Replace all `std::chrono` usages by `Stopwatch`, `TimeSpan` and `DateTime`~~
- ~~Credit external dependencies in README~~
- Add a way to use stereo audio files as mono sources and vice-versa
- Add an API to edit compute shaders local size from C++
