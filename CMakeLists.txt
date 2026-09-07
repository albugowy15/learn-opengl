cmake_minimum_required(VERSION 3.20)

project(learn_opengl VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# Each lesson is deliberately a standalone executable.  That makes every
# checkpoint independently buildable and prevents later lessons from changing
# an earlier example.
function(add_lesson target lesson_directory)
  add_executable(${target}
      ${lesson_directory}/main.cpp
      glad/src/gl.c
  )

  target_include_directories(${target} PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

  target_link_libraries(${target} PRIVATE
      glfw
      OpenGL::GL
  )

  target_compile_options(${target} PRIVATE
      $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
  )
endfunction()

add_lesson(lesson_1_1_triangle lessons/1.1.triangle)
add_lesson(lesson_1_2_rectangle lessons/1.2.rectangle)
