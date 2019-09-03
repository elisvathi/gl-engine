#pragma once
#include "View.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "SceneMaterial.hpp"
#include "SceneObject.hpp"
#include <vector>
class Box : public SceneObject {
    public:
	Box(SceneMaterial *mat) : SceneObject(mat)
	{
	}

    protected:
	virtual int getNumberOfTriangles()
	{
		return 12;
	}
	virtual std::vector<GLfloat> getVertexData()
	{
		std::vector<GLfloat> data{
			-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,
			1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
			1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f,
			1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,
			-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
			1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
			1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f,
			1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  -1.0f,
			1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f,
			1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,
			-1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,
			1.0f,  1.0f,  -1.0f, 1.0f
		};
		return data;
	}

	virtual std::vector<GLfloat> getNormalsData()
	{
		return std::vector<GLfloat>();
	}

	virtual std::vector<GLfloat> getUvData()
	{
		std::vector<GLfloat> data{
			0.000059f, 1.0f - 0.000004f, 0.000103f, 0.336048f,
			0.335973f, 0.335903f,	1.000023f, 0.000013f,
			0.667979f, 0.335851f,	0.999958f, 0.336064f,
			0.667979f, 0.335851f,	0.336024f, 0.671877f,
			0.667969f, 0.671889f,	1.000023f, 0.000013f,
			0.668104f, 0.000013f,	0.667979f, 0.335851f,
			0.000059f, 0.000004f,	0.335973f, 0.335903f,
			0.336098f, 0.000071f,	0.667979f, 0.335851f,
			0.335973f, 0.335903f,	0.336024f, 0.671877f,
			1.000004f, 0.671847f,	0.999958f, 0.336064f,
			0.667979f, 0.335851f,	0.668104f, 0.000013f,
			0.335973f, 0.335903f,	0.667979f, 0.335851f,
			0.335973f, 0.335903f,	0.668104f, 0.000013f,
			0.336098f, 0.000071f,	0.000103f, 0.336048f,
			0.000004f, 0.671870f,	0.336024f, 0.671877f,
			0.000103f, 0.336048f,	0.336024f, 0.671877f,
			0.335973f, 0.335903f,	0.667969f, 0.671889f,
			1.000004f, 0.671847f,	0.667979f, 0.335851f
		};
		return data;
	}
};
