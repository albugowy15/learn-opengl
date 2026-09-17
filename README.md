# Learn OpenGL

A small C++20 workspace for following [LearnOpenGL](https://learnopengl.com/).
Every lesson and exercise is a standalone executable, while reusable code lives
in one shared module.

## Build

The project requires CMake, a C++20 compiler, and desktop OpenGL development
files. GLFW and GLAD are already vendored and are built automatically.

### Arch Linux

```sh
sudo pacman -Syu --needed base-devel cmake mesa \
    libx11 libxrandr libxinerama libxcursor libxi \
    wayland libxkbcommon wayland-protocols
```

### Debian and Ubuntu

```sh
sudo apt update
sudo apt install build-essential cmake pkg-config \
    libgl1-mesa-dev libegl1-mesa-dev \
    libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
    libwayland-dev libxkbcommon-dev wayland-protocols
```

Configure and build everything from the repository root:

```sh
cmake -S . -B build
cmake --build build
```

Build and run one example:

```sh
cmake --build build --target lesson_1_6_shaderclass
./build/lesson_1_6_shaderclass
```

## Adding a lesson or exercise

Create a directory containing `main.cpp`:

```text
lessons/1.7.textures/
├── main.cpp
└── shaders/        # Optional lesson-local assets
```

Register it at the bottom of `CMakeLists.txt`:

```cmake
add_opengl_example(lesson_1_7_textures lessons/1.7.textures)
```

CMake defines `LEARNOPENGL_EXAMPLE_DIR` for each executable. Use it when
opening lesson-local assets so the program works regardless of the directory
from which it is launched:

```cpp
const char* path = LEARNOPENGL_EXAMPLE_DIR "/shaders/texture.vs";
```

## Adding reusable code

For a reusable module, place its interface and implementation separately:

```text
include/learnopengl/camera.h
src/camera.cpp
```

Create a library target for it and link only the lessons that use it. The
`learnopengl_shader` target in `CMakeLists.txt` is the example to follow.
