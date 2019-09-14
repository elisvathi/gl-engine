#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
class G_Camera {
    public:
	float fov = 55.0f;
	float near = 0.1f;
	float far = 100.0f;
	float aspectRatio;
	vec3 position = vec3(3, 3, 3);
	vec3 look = vec3(0, 0, 0);
	vec3 up = vec3(0, 1, 0);

	G_Camera(int w, int h) : aspectRatio(float(w) / float(h))
	{
	}

	G_Camera(float ar) : aspectRatio(ar)
	{
	}

	mat4 get_vp_matrix()
	{
		return get_perspective() * get_look_at();
	}

	vec3 get_position()
	{
		return position;
	}

	void set_position(vec3 pos)
	{
		position = pos;
	}

	float get_fov()
	{
		return fov;
	}

	void set_fov(float val)
	{
		fov = val;
	}

	vec3 get_target()
	{
		return look;
	}

	void set_target(vec3 t)
	{
		look = t;
	}

  float get_aspect_ratio(){
    return aspectRatio;
  }
  void set_aspect_ratio(float ar){
    aspectRatio = ar;
  }

	vec3 get_direction()
	{
		return normalize(look - position);
	}

    private:

	vec3 get_up_vector()
	{
		return normalize(((look - position) * up) * (look - position));
	}


	mat4 get_look_at()
	{
		return lookAt(position, look, up);
	}

	mat4 get_perspective()
	{
		return perspective(radians(fov), aspectRatio, near, far);
	}
};
