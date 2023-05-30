# Template For C++ Projects

![C++](https://img.shields.io/badge/C%2B%2B-11%2F14%2F17%2F20%2F23-blue)
![License](https://camo.githubusercontent.com/890acbdcb87868b382af9a4b1fac507b9659d9bf/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6c6963656e73652d4d49542d626c75652e737667)
[![Ubuntu CI Test](https://github.com/kybuivan/sdl-tutorials/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/kybuivan/sdl-tutorials/actions/workflows/ubuntu.yml)
[![Windows CI Test](https://github.com/kybuivan/sdl-tutorials/actions/workflows/windows.yml/badge.svg)](https://github.com/kybuivan/sdl-tutorials/actions/workflows/windows.yml)
[![MacOS CI Test](https://github.com/kybuivan/sdl-tutorials/actions/workflows/macos.yml/badge.svg)](https://github.com/kybuivan/sdl-tutorials/actions/workflows/macos.yml)


This is a template for C++ projects. What you get:

- Library, executable and test code separated in distinct folders
- Use of modern CMake for building and compiling
- External libraries installed and managed by [CPM](https://github.com/cpm-cmake/CPM.cmake) Package Manager
- Unit testing using [Catch2](https://github.com/catchorg/Catch2) v2
- General purpose libraries: [JSON](https://github.com/nlohmann/json), [spdlog](https://github.com/gabime/spdlog), [cxxopts](https://github.com/jarro2783/cxxopts) and [fmt](https://github.com/fmtlib/fmt)
- Continuous integration testing with Github Actions and [pre-commit](https://pre-commit.com/)
- Code documentation with [Doxygen](https://doxygen.nl/) and [Github Pages](https://franneck94.github.io/CppProjectTemplate/)
- Tooling: Clang-Format, Cmake-Format, Clang-tidy, Sanitizers

## Structure

``` text
├── CMakeLists.txt
├── app
│   ├── CMakesLists.txt
│   └── main.cc
├── cmake
│   └── cmake modules
├── docs
│   ├── Doxyfile
│   └── html/
├── src
│   ├── CMakesLists.txt
│   ├── my_lib.h
│   └── my_lib.cc
└── tests
    ├── CMakeLists.txt
    └── main.cc
```

Library code goes into [src/](src/), main program code in [app/](app) and tests go in [tests/](tests/).

## Software Requirements

- CMake 3.21+
- GNU Makefile
- Doxygen
- CPM
- MSVC 2017 (or higher), G++9 (or higher), Clang++9 (or higher)
- Optional: Code Coverage (only on GNU|Clang): lcov, gcovr
- Optional: Makefile, Doxygen

## Building

First, clone this repo and do the preliminary work:

```shell
git clone https://github.com/kybuivan/sdl-tutorials.git
make prepare
```

- App Executable

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --target main
cd app
./main
```

- Unit testing

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug --target unit_tests
cd tests
./unit_tests
```

- Documentation

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug --target docs
```

- Output

```shell
JSON: 3.11.2
FMT: 90100
CXXOPTS: 3.1.1
SPDLOG: 1.11.0
SDL: 2.26.3
SDL_image: 2.6.3
SDL_mixer: 2.6.3
SDL_net: 2.2.0
SDL_ttf: 2.20.2


Usage Example:
[2023-05-30 13:32:54.175] [info] Welcome to sdl-tutorials v0.1.0

Welcome to sdl-tutorials v0.1.0

Usage:
  sdl-tutorials [OPTION...]

 arguments options:
  -h, --help          Print usage
  -f, --filename arg  File name
  -v, --verbose       Verbose output
```
For more info about CMake see [here](./README_cmake.md).
