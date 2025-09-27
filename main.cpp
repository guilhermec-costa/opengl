#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void) {
  GLFWwindow* window;

  if(!glfwInit())
    return -1;
  
  window = glfwCreateWindow(900, 600, "Window", NULL, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if(glewInit() != GLEW_OK) {
    std::cout << "Error to initialize glew\n";
  };

  // vertex buffer object: memory buffer in the gpu vram
  unsigned int vbo;
  glGenBuffers(1, &vbo); // gives back the buffer id and creates a buffer in the opengl state machine
  glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind vbo to opengl target

  float trg_vertexes[6] = {
    -0.5f, -0.5f, 
    0.0f, 0.5f, 
    0.5f, -0.5f
  };
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), trg_vertexes, GL_STATIC_DRAW);

  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3); // this is the draw call made on the CPU

    // glBegin(GL_TRIANGLES);
    //   glVertex2f(-0.5f, -0.5f);
    //   glVertex2f(0.0f, 0.5f);
    //   glVertex2f(0.5f, -0.5f);
    // glEnd();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
