cmake_minimum_required(VERSION 3.20)

project(learn_opengl VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)

# GLFW and GLAD are vendored, so configuring this project is enough to build
# its OpenGL dependencies.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw EXCLUDE_FROM_ALL)

add_library(opengl_runtime STATIC glad/src/gl.c)
target_include_directories(opengl_runtime PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(opengl_runtime PUBLIC
    glfw
    OpenGL::GL
)

add_library(learnopengl_shader STATIC src/shader.cpp)
target_include_directories(learnopengl_shader PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(learnopengl_shader PUBLIC opengl_runtime)
target_compile_options(learnopengl_shader PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
)

# Each lesson and exercise is a standalone executable. That keeps every
# checkpoint independently buildable and prevents later examples from changing
# an earlier one.
function(add_opengl_example target example_directory)
  add_executable(${target} ${example_directory}/main.cpp)

  target_link_libraries(${target} PRIVATE opengl_runtime)

  target_compile_definitions(${target} PRIVATE
      LEARNOPENGL_EXAMPLE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/${example_directory}"
  )

  target_compile_options(${target} PRIVATE
      $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
  )
endfunction()

add_opengl_example(lesson_1_1_triangle lessons/1.1.triangle)
add_opengl_example(lesson_1_2_rectangle lessons/1.2.rectangle)
add_opengl_example(lesson_1_3_shader lessons/1.3.shader)
add_opengl_example(lesson_1_4_uniform lessons/1.4.uniform)
add_opengl_example(lesson_1_5_attributes lessons/1.5.attributes)
add_opengl_example(lesson_1_6_shaderclass lessons/1.6.shaderclass)
target_link_libraries(lesson_1_6_shaderclass PRIVATE learnopengl_shader)
add_opengl_example(exercise_1_1 exercises/1.1)
add_opengl_example(exercise_1_2 exercises/1.2)
add_opengl_example(exercise_1_3 exercises/1.3)
add_opengl_example(exercise_1_4 exercises/1.4)
target_link_libraries(exercise_1_4 PRIVATE learnopengl_shader)
