#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;
class G_Node {
public:
	G_Node(vec3 pos = vec3(0, 0, 0), vec3 sc = vec3(1.0f, 1.0f, 1.0f),
	     vec3 rot = vec3(0, 0, 0))
		: positionVector(pos), scaleVector(sc), rotationVector(rot)
	{
	}
	mat4 get_object_matrix()
	{
		return getTranslateMatrix() * getRotationMatrix() *
      getScaleMatrix();
	}
	vec3 getPosition()
	{
		return positionVector;
	}
	void setPosition(vec3 pos)
	{
		positionVector = pos;
	}

private:
	vec3 positionVector;
	vec3 scaleVector;
	vec3 rotationVector;
	mat4 getScaleMatrix()
	{
		return mat4(1.0f);
	}

	mat4 getRotationMatrix()
	{
		return mat4(1.0f);
	}

	mat4 getTranslateMatrix()
	{
		return translate(mat4(), positionVector);
	}
};
