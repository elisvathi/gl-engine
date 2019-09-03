#pragma once
#include <GL/glew.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include "Utils.hpp"
using namespace glm;

static double lastTime = glfwGetTime();
class Camera {
public:
  float fov = 45.0f;

  float near = 0.1f;
  float far = 100.0f;

  int *width = nullptr;
  int *height = nullptr;

  float time = 0.0f;
  float radius = 5.0f;
  float posHeight = 0.5f;
  vec3 lookat;
  vec3 up;

  GLFWwindow  * window;

  Camera(int* w, int* h, GLFWwindow *win): width(w), height(h), window(win) {
    build();
  }

  ~Camera(){

  }

  mat4 getPerspectiveMatrix() {
    return perspective(radians(getFov()), getAspectRatio(), near, far);
  }

  mat4 getLookAt() {
    return lookAt(getPosition(), lookat, up);
  }

  mat4 getVpMatrix(){
    return getPerspectiveMatrix() * getLookAt();
  }

  void updateFrame() {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    time = map(x, 0, *width, 0, 3.14 * 2);
    posHeight = map(y, 0, *height, -10, 10);
  }

private:

  vec3 getDirection(){
    return normalize(lookat - getPosition());
  }

  vec3 right(){
    return normalize(getDirection() * up);
  }

  void build(){
    lookat = vec3(0,0,0);
    up = vec3(0,1,0);
  }

  vec3 getPosition(){
    return vec3(radius * cos(time), float(posHeight),radius * sin(time));
  }

  float getFov(){
    return fov;
  }

  float getAspectRatio() { return (float)*width / (float)*height; }
};
