#pragma once
#include <GL/glew.h>
#include "Shaders.hpp"
#include <glm/glm.hpp>
#include <string>
using namespace std;
using namespace glm;
class SceneMaterial {
public:
  GLuint programID;
  SceneMaterial(const char *vertex_path, const char *fragment_path) {
    programID = buildProgram(vertex_path, fragment_path);
  }

  virtual vec3 getColor() {
    return vec3(0,0,0);
  }

  virtual vec3 getColor(int vertexIndex) {
    return vec3(0,0,0);
  }

  ~SceneMaterial() { glDeleteProgram(programID); }
};

class ColorMaterial : public SceneMaterial {
public:
  vec3 color;
  ColorMaterial(vec3 col): SceneMaterial(string("shaders/vertex.glsl").c_str(), string("shaders/colorshader.glsl").c_str()),  color(col){
  }

  virtual vec3 getColor() {
    return color;
  }

  virtual vec3 getColor(int vertexIndex) {
    return color;
  }
};
