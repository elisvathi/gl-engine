#pragma once
#include <glm/glm.hpp>
#include "G_Vertex.hpp"
#include <vector>
using namespace std;
using namespace glm;

class G_Vertex_Collection {
    public:

	vector<G_Vertex> vertices;

  G_Vertex_Collection(){}

  void add_vertex(G_Vertex v){
    vertices.push_back(v);
  }

  void add_vertex(vec3 v){
    vertices.push_back(G_Vertex(v));
  }

};
