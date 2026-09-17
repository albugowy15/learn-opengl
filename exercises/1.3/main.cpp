#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

const char *vertex_shader_source = R"(
#version 330 core
layout(location = 0) in vec3 a_position;

void main() {
  gl_Position = vec4(a_position, 1.0);
}
)";

const char *orange_fragment_shader_source = R"(
#version 330 core
out vec4 fragment_color;

void main() {
  fragment_color = vec4(1.0, 0.5, 0.2, 1.0);
}
)";

const char *yellow_fragment_shader_source = R"(
#version 330 core
out vec4 fragment_color;

void main() {
  fragment_color = vec4(1.0, 1.0, 0.0, 1.0);
}
)";
void framebufferSizeCallback(GLFWwindow *, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

int main() {
  if (glfwInit() == GLFW_FALSE) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Exercise 1.2", nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  if (gladLoadGL(glfwGetProcAddress) == 0) {
    std::cerr << "Failed to initialize GLAD\n";
    glfwTerminate();
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glViewport(0, 0, 800, 600);

  // clang-format off
  const float firstTriangleVertices[] = {
    // left equilateral triangle
    -0.8f, -0.5f, 0.0f,
     0.0f, -0.5f, 0.0f,
    -0.4f,  0.19282f, 0.0f,
  };

  const float secondTriangleVertices[] = {
    // right equilateral triangle
     0.0f, -0.5f, 0.0f,
     0.8f, -0.5f, 0.0f,
     0.4f,  0.19282f, 0.0f,
  };
  // clang-format on

  const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex_shader_source, nullptr);
  glCompileShader(vertexShader);

  const unsigned int orangeFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(orangeFragmentShader, 1, &orange_fragment_shader_source,
                 nullptr);
  glCompileShader(orangeFragmentShader);

  const unsigned int yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(yellowFragmentShader, 1, &yellow_fragment_shader_source,
                 nullptr);
  glCompileShader(yellowFragmentShader);

  const unsigned int orangeFragmentShaderProgram = glCreateProgram();
  glAttachShader(orangeFragmentShaderProgram, vertexShader);
  glAttachShader(orangeFragmentShaderProgram, orangeFragmentShader);
  glLinkProgram(orangeFragmentShaderProgram);
  glDeleteShader(orangeFragmentShader);

  const unsigned int yellowFragmentShaderProgram = glCreateProgram();
  glAttachShader(yellowFragmentShaderProgram, vertexShader);
  glAttachShader(yellowFragmentShaderProgram, yellowFragmentShader);
  glLinkProgram(yellowFragmentShaderProgram);
  glDeleteShader(yellowFragmentShader);

  // delete
  glDeleteShader(vertexShader);

  // first vao and vbo for first triangle
  unsigned int firstTriangleVAO = 0;
  unsigned int firstTriangleVBO = 0;
  glGenVertexArrays(1, &firstTriangleVAO);
  glGenBuffers(1, &firstTriangleVBO);
  glBindVertexArray(firstTriangleVAO);
  glBindBuffer(GL_ARRAY_BUFFER, firstTriangleVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangleVertices),
               firstTriangleVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // second vao and vbo for second triangle
  unsigned int secondTriangleVAO = 0;
  unsigned int secondTriangleVBO = 0;
  glGenVertexArrays(1, &secondTriangleVAO);
  glGenBuffers(1, &secondTriangleVBO);
  glBindVertexArray(secondTriangleVAO);
  glBindBuffer(GL_ARRAY_BUFFER, secondTriangleVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangleVertices),
               secondTriangleVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  while (glfwWindowShouldClose(window) == GLFW_FALSE) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw first triangle
    glUseProgram(orangeFragmentShaderProgram);
    glBindVertexArray(firstTriangleVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(yellowFragmentShaderProgram);
    glBindVertexArray(secondTriangleVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &firstTriangleVAO);
  glDeleteBuffers(1, &firstTriangleVBO);

  glDeleteVertexArrays(1, &secondTriangleVAO);
  glDeleteBuffers(1, &secondTriangleVBO);
  glDeleteProgram(orangeFragmentShaderProgram);
  glfwTerminate();
  return 0;
}
