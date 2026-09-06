# Learn OpenGL

Minimal C++ project using CMake, GLFW, GLAD, and desktop OpenGL.

## Project layout

GLAD's generated headers are part of the project's public include tree, while
its generated C implementation remains in `glad/src`:

```text
include/
├── glad/gl.h
└── KHR/khrplatform.h
glad/
└── src/gl.c
src/
└── main.cpp
```

`gl.c` is normal in a C++ project: CMake compiles it as C and links it with the
C++ executable. `main.cpp` includes `glad/gl.h` before GLFW and initializes
GLAD after GLFW creates the OpenGL context.

## Build and run

```sh
cmake -S . -B build
cmake --build build
./build/learn_opengl
```

Install GLFW first, for example from its source checkout:

```sh
cd ../glfw
cmake -S . -B build
cmake --build build
sudo cmake --install build
```

On Debian/Ubuntu, install the remaining build and OpenGL development files with:

```sh
sudo apt install build-essential cmake libgl1-mesa-dev
```

The current program opens an 800×600 OpenGL 3.3 Core window. Press Escape or
close the window to exit.
