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

  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
      glVertex2f(-0.5f, -0.5f);
      glVertex2f(0.0f, 0.5f);
      glVertex2f(0.5f, -0.5f);
    glEnd();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
