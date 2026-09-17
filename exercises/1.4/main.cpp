#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>

#include <iostream>

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
      glfwCreateWindow(800, 600, "Lesson 1.1: Triangle", nullptr, nullptr);
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
  const float vertices[] = {
    // first triangle
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f,
  };
  // clang-format on

  Shader ourShader(LEARNOPENGL_EXAMPLE_DIR "/shaders/shader.vs",
                   LEARNOPENGL_EXAMPLE_DIR "/shaders/shader.fs");

  unsigned int VAO = 0;
  unsigned int VBO = 0;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // Configure the VAO once. It remembers that attribute 0 reads from vbo.
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  while (glfwWindowShouldClose(window) == GLFW_FALSE) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.use();
    ourShader.setFloat("horizontalOffset", 0.5);
    // glUniform1f(vertexLocation, 0.25f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
  return 0;
}
