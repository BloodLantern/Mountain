# Mountain

A C++ Framework for making 2D games.

## Documentation

The Doxygen documentation can be found [online](https://codedocs.xyz/BloodLantern/Mountain/index.html) or manually generated using the Doxyfile.

## How to use this library

You can choose between 3 ways of using this framework for your projects.

### 1. Use this as a submodule

In a directory of your choice within your project, run `git submodule add https://github.com/BloodLantern/Mountain.git`

Add the `Mountain/Mountain/Mountain.vcxproj` project to your solution and set your build order to build it first.
In your project configuration, add the `Mountain/Mountain/include` folder to your include path.
Also add the `Mountain/bin` folder to your additional library directories.
The last thing to do is to statically link your application to `toolboxd.lib` in `Debug` (`/O0`), and to `toolbox.lib` in `Release` (`/O2`).

### 2. Build from source

Clone the project using `git clone https://github.com/BloodLantern/Mountain.git`.
Open the Visual Studio solution file found in the root directory.
After opening it, the only thing you have to do is to build the library (Mountain project) in Debug and then in Release mode.

The build events will automatically create a `Mountain/bin` folder.
In that folder, you will find the `.lib`, `.pdb` and `.idb` files for `Debug` (`/O0`) and `Release` (`/O2`).
For the `Debug` version, the file names will be suffixed with a 'd'.
Additionally, the `include` directory, in which all the header files are located, can be found in the `Mountain` folder.

To then use the library in any of your projects, do as you would usually: include the necessary headers and compile by statically linking the corresponding library files (`Debug` or `Release`).
