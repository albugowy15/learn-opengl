# Lesson 1.2: Rectangle

Draws a rectangle as two triangles. Unlike the triangle lesson, this example
uses an element buffer object (EBO) and `glDrawElements`. The index list reuses
the rectangle's four vertices instead of repeating two of them.

The EBO binding is part of the VAO state, so binding this lesson's VAO during
rendering also selects its index buffer.

Build and run from the repository root:

```sh
cmake --build build --target lesson_1_2_rectangle
./build/lesson_1_2_rectangle
```
