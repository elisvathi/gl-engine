#pragma once
#include <glm/glm.hpp>
#include "G_Vertex_Collection.hpp"
using namespace glm;
class G_Triangle {
public:
  vec3 indices;
  vec2 first_uv = vec2(0,0);
  vec2 second_uv = vec2(0,1);
  vec2 third_uv = vec2(1,1);
  G_Triangle(int first, int second, int third):indices(vec3(first,second, third)){

  }

  vec3 get_normal(G_Vertex_Collection * coll){
    return normalize(cross(get_first_direction(coll), get_second_direction(coll)));
  }

  int operator[](int i) {
    if (i == 0) {
      return int(indices.x);
    } else if (i == 1) {
      return int(indices.y);
    }
    return int(indices.z);
  }

  bool get_vertices(G_Vertex_Collection* coll, vec3& first, vec3& second, vec3& third) {
    first = coll->vertices[int(indices.x)].position;
    second = coll->vertices[int(indices.y)].position;
    third = coll->vertices[int(indices.z)].position;
    return true;
  }

  bool contains_index(int i) {
    return int(indices.x) == i || int(indices.y) == i || int(indices.z) == i;
  }
  bool share_same_vertices(G_Triangle other) {
    for(int i = 0; i< 3; i++){
      for(int j = 0; j < 3; j++){
        if((*this)[i] == other[j]){
          return true;
        }
      }
    }
    return false;
  }

private:
  vec3 get_first_direction(G_Vertex_Collection* coll){
    vec3 first, second, third;
    get_vertices(coll, first, second,third);
    return normalize(second-first);
  }
  vec3 get_second_direction(G_Vertex_Collection* coll){
    vec3 first, second, third;
    get_vertices(coll, first, second,third);
    return normalize(third-first);
  }
};
