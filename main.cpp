#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader);

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

  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // vertex buffer object: memory buffer in the gpu vram
  unsigned int vbo;
  glGenBuffers(1, &vbo); // gives back the buffer id and creates a buffer in the opengl state machine
  glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind vbo to opengl target

  float positions[6] = {
    -0.5f, -0.5f, // vertex, containing only position attribute
    0.0f, 0.5f,  // vertex
    0.5f, -0.5f // vertex
  };

  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0); // for each attribute definition

 const std::string vertex_shader = R"glsl(
  #version 330 core

  layout(location = 0) in vec4 position;

  void main(){
    gl_Position = position;
  }
  )glsl"; 

  const std::string fragment_shader = R"glsl(
  #version 330 core

  layout(location = 0) out vec4 color;

  void main(){
    color= vec4(1.0, 0.0, 0.0, 1.0);
  }
  
  )glsl";

  unsigned int shader = create_shader(vertex_shader, fragment_shader);
  glUseProgram(shader);

  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3); // this is the draw call made on the CPU
    // after this point, gpu processing begins. Vertex shader gets called, and fragment shaders get called
    // vertex shaders are called for each vertex that will be rendered, and their purpose is to tell where the vertex should be rendered on the window
    // vertex shaders know the position based on the index specified in the state of the vertex that contains the positions.
    


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

static unsigned int compile_shader(unsigned int type, const std::string& source) {
  unsigned int id = glCreateShader(type);
  const char* _str = source.c_str();
  glShaderSource(id, 1, &_str, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if(result == GL_FALSE) {
    int err_msg_len;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &err_msg_len);
    char message[err_msg_len];
    glGetShaderInfoLog(id, err_msg_len, &err_msg_len, message);
    std::cout << "failed to compile shader: (" << 
    (type == GL_VERTEX_SHADER ? "VERTEX SHADER" : "FRAGMENT SHADER") << ")" 
    << message << std::endl;
    glDeleteShader(id);
    return 0;
  }
  return id;
};

static unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
  unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);
  return program;
};