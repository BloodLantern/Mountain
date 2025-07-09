# Mountain

A (currently) Windows-only C++ Framework for making 2D games.
It will certainly become available for Linux as well at some point.

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

### 1. Use this as a submodule (recommended)

In a directory of your choice within your project, run `git submodule add --recurse-submodule https://github.com/BloodLantern/Mountain.git`

Add the `Mountain/Mountain.vcxproj` project to your solution and set it as a reference to your project using `Add > Reference...`.
In your project configuration, add the `Mountain/src`, `Mountain/externals/src` and `MathToolbox/src` folders to your include path.

### 2. Build from source

Clone the project using `git clone https://github.com/BloodLantern/Mountain.git`.
Open the Visual Studio solution file found in the root directory.
After opening it, the only thing you have to do is to build the framework (Mountain project) in `Debug` and then in `Release` mode.

All the binaries can be found in the `x64/(Debug|Release)` folder.
Additionally, copy the header files from `Mountain/src`.
As the framework changes, you might also need to get some header files from `Mountain/externals/src`.
In its current state, you need the `ImGui` and `magic_enum` folders.
You also need the math headers, which are located in `MathToolbox/src`.

To then use the framework in any of your projects, do as you would usually: include the necessary headers,
compile by statically linking against the corresponding `Mountain.lib`
(`Debug` or `Release`) and add the correct `Mountain.dll` to your executable file directory.

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
  - Blur
  - Noise
  - Mosaic
  - Grayscale
- Make gamepad input work for both Xbox, PS and Switch controllers
- Low-level audio API
- `Audio::Play()` static function
- \[WIP] Low-level graphics API
- \[WIP] `Scene` class
- Linux support
- ~~Automatic `std::formatter` implementation for all classes that define a `ToString()` function~~
- ~~Automatic `std::hash` implementation for all classes that define a `GetHashCode()` function~~
- Gamepad rumble support
- Gamepad gyro support
- ~~`Coroutine` class~~
- ~~Compute shader API~~
- ~~Custom exceptions~~
- Built-in shader hot-reloading
- Real unit tests
- Replace all `std::array` and `std::vector` usages with `Mountain::Array` and `Mountain::List`
- True text rendering
