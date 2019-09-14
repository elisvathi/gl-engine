#pragma once
#include <vector>
#include "G_Camera.hpp"
#include "G_Object.hpp"
#include "G_Light.hpp"

using namespace std;

class G_Scene{
public:

  vector<G_Object*> objects;
  G_Camera *camera;
  G_Light *light;

  G_Scene(G_Camera *cam, G_Light *l):camera(cam), light(l){
  }

  void add_object(G_Object *object){
    objects.push_back(object);
  }

  void build(){
    for(int i = 0; i< int(objects.size()); i++){
      objects[i]->build_object();
    }
  }

  void draw(){
    for(int i = 0; i< int(objects.size()); i++){
      objects[i]->draw_object(camera, light);
    }
  }

};
