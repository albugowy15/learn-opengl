# Learn OpenGL

Learning project for modern desktop OpenGL, following the tutorials and examples from [LearnOpenGL](https://learnopengl.com/). It uses CMake, GLFW, and GLAD as a small, incremental environment for working through the material.

## Setup

This project is developed and tested on Linux. The instructions below cover Arch Linux, the distribution currently used for development, and Debian/Ubuntu. For other operating systems or package managers, consult GLFW's [compilation guide](https://www.glfw.org/docs/latest/compile.html) and the [LearnOpenGL window-creation tutorial](https://learnopengl.com/Getting-started/Creating-a-window) for platform-specific prerequisites.

The project needs a C++20 compiler, CMake, and desktop OpenGL development files. Do not install GLFW or GLAD from a distribution package: GLFW is built from the vendored `glfw/` source below, and the top-level build compiles the vendored GLAD source, `glad/src/gl.c`, directly.

### Arch Linux

Install the toolchain, CMake, Mesa's OpenGL implementation, and GLFW's X11 and Wayland build dependencies:

```sh
sudo pacman -Syu --needed base-devel cmake mesa \
    libx11 libxrandr libxinerama libxcursor libxi \
    wayland libxkbcommon wayland-protocols
```

Do not install the `glfw` or `glad` packages. Continue with [Build and install GLFW from source](#build-and-install-glfw-from-source).

### Debian and Ubuntu

Install the compiler, CMake, OpenGL headers, and the native libraries GLFW uses for X11 and Wayland:

```sh
sudo apt update
sudo apt install build-essential cmake pkg-config \
    libgl1-mesa-dev libegl1-mesa-dev \
    libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
    libwayland-dev libxkbcommon-dev
```

### Build and install GLFW from source

This repository includes GLFW in `glfw/`. Build and install it once so the project's `find_package(glfw3 CONFIG REQUIRED)` call can find its CMake package:

```sh
cmake -S glfw -B glfw/build -DCMAKE_BUILD_TYPE=Release
cmake --build glfw/build
sudo cmake --install glfw/build
```

If you prefer not to install system-wide, choose a writable prefix and pass it to both CMake configurations:

```sh
cmake -S glfw -B glfw/build -DCMAKE_INSTALL_PREFIX="$PWD/.local"
cmake --build glfw/build
cmake --install glfw/build
cmake -S . -B build -DCMAKE_PREFIX_PATH="$PWD/.local"
```

### GLAD source

GLAD's generated headers and C implementation are already included in this repository. It is not installed separately: `CMakeLists.txt` compiles `glad/src/gl.c` and links it into the executable. Source files that use OpenGL functions must include GLAD before GLFW:

```cpp
#include <glad/gl.h>
#include <GLFW/glfw3.h>
```

## Build and run

Configure the project once, then build it:

```sh
cmake -S . -B build
cmake --build build
./build/learn_opengl
```

`cmake -S . -B build` reads `CMakeLists.txt`, finds the installed GLFW CMake package, and generates the build files in `build/`. `cmake --build build` uses those files to compile and link `learn_opengl`.

After editing `src/main.cpp` or another existing source file, run only `cmake --build build`; CMake rebuilds the files that changed. Run `cmake -S . -B build` again after changing `CMakeLists.txt`, adding or removing source files, or changing build options.
