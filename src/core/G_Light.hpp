#pragma once
#include <glm/glm.hpp>
using namespace glm;
class G_Light{
public:
  vec3 position;
  vec3 direction;
  vec3 color;
  G_Light(vec3 p, vec3 d, vec3 col): position(p), direction(d), color(col){}
};
