# Mountain

A (currently) Windows-only C++ Framework for making 2D games.

## Language version and architecture

This project is compiled using C++23 features (`/std:c++latest`), on MSVC, for the `x64` architecture.

## Samples

Sample projects are available in the [Samples](https://github.com/BloodLantern/Mountain.Samples) repository.

## Documentation

The Doxygen documentation can be found [online](https://codedocs.xyz/BloodLantern/Mountain/index.html) or manually generated using the `Doxyfile`.

Most types and functions have documentation in their respective header files so you can always check them if needed.

## How to use this library

You can choose between 2 ways of using this framework for your projects.

### 1. Use this as a submodule

In a directory of your choice within your project, run `git submodule add https://github.com/BloodLantern/Mountain.git`

Add the `Mountain/Mountain.vcxproj` project to your solution and set it as a reference to your project using `Add > Reference...`.
In your project configuration, add the `Mountain/include`, `Mountain/inline` and `Mountain/externals/include` folders to your include path.
One last thing is to globally define `MATH_TOOLBOX_DLL_IMPORT`.

### 2. Build from source

Clone the project using `git clone https://github.com/BloodLantern/Mountain.git`.
Open the Visual Studio solution file found in the root directory.
After opening it, the only thing you have to do is to build the library (Mountain project) in `Debug` and then in `Release` mode.

All the binaries can be found in the `x64/(Debug|Release)` folder.
Additionally, copy the headers files from the `Mountain/include` and `Mountain/inline`. As the library changes, you might also need to get some header files from `Mountain/externals/include`. In the current state, you need the `Maths`, `ImGui` and `magic_enum` folders.

To then use the library in any of your projects, do as you would usually: include the necessary headers, compile by statically linking against the corresponding `Mountain.lib` (`Debug` or `Release`) and add the correct `Mountain.dll` to your executable file directory.
