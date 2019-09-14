#pragma once
#include "G_Camera.hpp"
#include <GLFW/glfw3.h>
#include "G_Utils.hpp"
#include <iostream>
#include <math.h>
using namespace std;
class G_Camera_Rig {
public:
  double mouseX;
  double mouseY;
  int width;
  int height;
  G_Camera* camera;
  G_Camera_Rig(G_Camera* cam):camera(cam){}
  void update_frame(GLFWwindow *win) {
    glfwGetCursorPos(win , &mouseX, &mouseY);
    glfwGetWindowSize(win, &width, &height);
    update_camera();
  }
  void scrollCaptureFunction(GLFWwindow *w, double x, double y){
    update_scroll(x, y);
  }
protected:
  virtual void update_scroll(double x, double y){
    cout << "Scrolling X: "<< x << " Y: " << y << endl;
  }
  virtual void update_camera(){
    update_camera_aspect_ratio();
    update_camera_fov();
    update_camera_position();
    update_camera_target();
  }

  virtual void update_camera_position() = 0;
  virtual void update_camera_target() = 0;
  virtual void update_camera_fov() = 0;
  virtual void update_camera_aspect_ratio() {
    camera->set_aspect_ratio(float(width)/ float(height));
  }
};

class G_Orbit_Camera: public G_Camera_Rig {
public:
  float radius;
  G_Orbit_Camera(G_Camera* cam, float rad = 5): G_Camera_Rig(cam), radius(rad){
  }
protected:
  virtual void update_camera_position(){
    float time = map(float(mouseX), 0, float(width), 0, M_PI * 2);
    float camHeight = map(float(mouseY), 0, float(height), 10, -10);
    vec3 pos(radius * cos(time), camHeight, radius*sin(time));
    camera->set_position(pos);
  }

  void update_camera_target(){
  }
  virtual void update_camera_fov(){
  }

};

class G_LookAround_Camera: public G_Orbit_Camera{
public:
  G_LookAround_Camera(G_Camera* cam, float rad = 5): G_Orbit_Camera(cam, rad){
  }
  virtual void update_camera_position(){
    float time = map(float(mouseX), 0, float(width), 0, M_PI * 2);
    float camHeight = map(float(mouseY), 0, float(height), 10, -10);
    vec3 pos(radius * cos(time), camHeight, radius*sin(time));
    camera->set_target(pos);
  }
};
