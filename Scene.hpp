#pragma once
#include "SceneObject.hpp"
#include "View.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "SceneMaterial.hpp"
#include "SceneObject.hpp"
#include "Triangle.hpp"
#include "Box.hpp"
#include "ExternalObj.hpp"
#include <vector>
#include <string>

using namespace std;

class Scene {
public:
  // SceneObject **objects;
  vector<SceneObject*> objects;
  Camera *camera;
  Scene(Camera *cam) : camera(cam) {
    std::string vertexPath = "shaders/vertex.glsl";
    std::string fragmentPath = "shaders/fragment.glsl";
    std::string colorPath = "shaders/colorshader.glsl";
    SceneMaterial *mat =
      new SceneMaterial(vertexPath.c_str(), fragmentPath.c_str());
    SceneMaterial *greenMat = new ColorMaterial(vec3(0, 1, 0));
    SceneMaterial *redMat = new ColorMaterial(vec3(1, 0, 0));
    SceneMaterial *blueMat = new ColorMaterial(vec3(0, 0, 1));
    SceneObject* box = new Box(mat);
    SceneObject* triangle1 = new Triangle(greenMat);
    SceneObject* triangle2 = new Triangle(redMat);
    SceneObject* triangle3 = new Triangle(blueMat);
    SceneObject* external = new ExternalObj(string("objects/box.obj").c_str(), blueMat);
    box->setPosition(vec3(0, 0,0));
    triangle1->setPosition(vec3(1, 1 , -0.8f));
    triangle2->setPosition(vec3(1, 1 ,0));
    triangle3->setPosition(vec3(1, 1 ,0.8f));
    objects.push_back(external);
    // objects.push_back(triangle1);
    // objects.push_back(triangle2);
    // objects.push_back(triangle3);
  }

  void build() {
    for(int i = 0; i < int(objects.size()); i++){
      objects[i]->buildBuffer(camera);
    }
  }
  void draw() {
    for(int i = 0; i < int(objects.size()); i++){
      objects[i]->draw();
    }
  }

  ~Scene() {
    for(int i = 0; i < int(objects.size()); i++){
      delete objects[i];
    }
    if (camera != nullptr) {
      delete camera;
    }
  }
};
