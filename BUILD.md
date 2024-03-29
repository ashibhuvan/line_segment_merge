# Building the project
## Prerequisites
You will need a C++14 compliant compiler, CMake, and a suitable development environment. The test was developed on MacOS using JetBrains CLion. It was verified to work on Windows under MS Visual Studio 2017 Community Edition 15.9.13 and VisualStudio 2019 Community Edition 16.1.3

We recommend CLion on MacOS (there's a 30 day evaluation license) or Visual Studio 2019 Community edition on Windows. Feel free to try other CMake-aware development environments.
## How to build
* MacOS/CLion: open the project in CLion, build, run the stub test.
* Windows/Visual Studio 2019: ask Visual Studio to clone this repo locally. It will open the project once done. Build, run the stub test.
* Windows/Visual Studio 2107: create a build folder outside of your repository. In your command prompt, execute ``cmake <path to your repository>``. That will create a Visual Studio solution. Open that in Visual Studio, build, run the stub test. Use Visual Studio to develop/debug. When you need to modify a project or the solution, change the CMakeLists.txt and rerun cmake.
## Troubleshooting
* Missing Google tests: this is a submodule. Be sure to run ``git submodule init`` and ``git submodule update``
* Visual Studio Test Explorer doesn't show any tests: did you enable the Google Test adapter?
