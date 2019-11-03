#include <stdlib.h>
#include <stdio.h>
#include <functional>
#include <iostream>

#include <ogl.h>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#include "app.hpp"
#include "framebuffer.hpp"
#include "texture.hpp"

#define FULLSCREEN 0
#define FPS 60


app* m_app;

void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
  exit(1);
}

void debugCallbackFun(GLenum source, GLenum type, GLuint id, GLenum severity,
                      GLsizei length,const GLchar *message, const void *userParam) {
    puts(message);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    glm::vec3 camera_position = m_app->get_camera_position();
    glm::vec3 look_at =  m_app->get_look_at();
    glm::vec3 up_vector = m_app->get_up_vector();
    glm::vec3 side = glm::cross(up_vector,look_at);

    float speed = 0.05;
    
    switch(key) {
    case GLFW_KEY_S:
        camera_position -= speed * look_at;
        break;
    case GLFW_KEY_W:
        camera_position += speed * look_at;
        break;
    case GLFW_KEY_A:
        camera_position -= speed * side;
        break;
    case GLFW_KEY_D:
        camera_position += speed * side;
        break;
    }

    printf("%f %f %f\n", camera_position.x, camera_position.y, camera_position.z);
    m_app->set_camera_position(camera_position);
}


int main(int argc, char *argv[]) {
  int frame;
  double prev_time;
  double curr_time;
  GLFWwindow *window;

  if (!glfwInit()) {
    fprintf(stderr, "glfw failed to initialize\n");
    exit(1);
  }
  
  glfwSetErrorCallback(error_callback);
 
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);

  int width = 800;
  int height = 800;
 
  window = glfwCreateWindow(width, height, "window",
	  FULLSCREEN ? glfwGetPrimaryMonitor() : NULL, NULL);  

  if (!window) {
    fprintf(stderr, "Failed to create window!\n");
    exit(1);
  }

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  glfwMakeContextCurrent(window);
  //glfwSwapInterval(1);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
      fprintf(stderr, "GLEW failed to initialize!\n");
      exit(1);
  }

  printf("Using GL version: %s\n", glGetString(GL_VERSION));
  printf("Using GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
  printf("%dfps, %dx%d, %s\n", FPS, width, height,
    FULLSCREEN ? "fullscreen" : "windowed");

  glEnable(GL_DEBUG_OUTPUT);
  //glDebugMessageCallback(debugCallbackFun, NULL);
 
  auto k_back = [] (GLFWwindow* window, int key, int
                    scancode, int state, int modifier) -> void {
                };
  glfwSetKeyCallback(window, key_callback);

  m_app = new app(glm::ivec2(width, height));
  glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
      app* m_app = (app*) glfwGetWindowUserPointer(window);
      m_app->resize(width, height);
  });
  glfwSetWindowUserPointer(window, (void*)m_app);



  /* Setup ImGUI */
  //IMGUI_CHECKVERSION();
  //ImGui::CreateContext();
  //ImGuiIO& io = ImGui::GetIO(); (void)io;
  //ImGui_ImplGlfwGL3_Init(window, true);
  //ImGui::StyleColorsDark();

  /* setup framebuffer */
  // auto fb_color_texture = texture::genTexture(GL_TEXTURE_2D);
  // fb_color_texture->texImage2D(0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT,
  //                              nullptr);
  // fb_color_texture->texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // fb_color_texture->texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // auto fb_depth_texture = texture::genTexture(GL_DEPTH_ATTACHMENT);
  // fb_depth_texture->texImage2D(0, GL_RGBA16F, width, height, 0, GL_DEPTH_COMPONENT,
  //                              GL_FLOAT, nullptr);
  // fb_depth_texture->texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // fb_depth_texture->texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // auto fb = framebuffer::genFramebuffer();
  // fb->framebufferTexture(fb_color_texture, GL_COLOR_ATTACHMENT0);
  // fb->framebufferTexture(fb_depth_texture, GL_DEPTH_ATTACHMENT);

  // if (GL_FRAMEBUFFER_COMPLETE != fb->checkFramebufferStatus()) {
  //     fprintf(stderr, "Framebuffer is not complete\n");
  //     exit(0);
  // }
  

  /* game loop */
  frame = 0;
  prev_time = -1.0;
  glfwSetTime(0.0);
  while (!glfwWindowShouldClose(window)) {
      curr_time = glfwGetTime();
      if (curr_time - prev_time >= 1.0 / FPS) {
          //ImGui_ImplGlfwGL3_NewFrame();
          
          glClearColor(0, 0, 0, 1);
          glClear(GL_COLOR_BUFFER_BIT);

          double xpos, ypos;
          glfwGetCursorPos(window, &xpos, &ypos);
          m_app->set_cursor_pos(xpos, ypos);

          //fb->bind();
          //m_app.draw(curr_time - prev_time);
          m_app->draw(curr_time);
          //fb->unbind();

          //ImTextureID texID = (ImTextureID) fb_color_texture->get_id();
          
          //ImGui::Render();
          //ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());          
          
      
          glfwSwapBuffers(window);

          glfwPollEvents();
          if (!(frame % 60)) {
              printf("%d frames rendered, %f s elapsed\n", frame, curr_time);
          }
          frame++;
          prev_time = curr_time; 
      }
  }

  
  ImGui_ImplGlfwGL3_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
}
