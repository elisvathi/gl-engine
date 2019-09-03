#pragma once
#include "View.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "SceneMaterial.hpp"
#include "SceneObject.hpp"
#include <vector>
class Triangle : public SceneObject {
    public:
	Triangle(SceneMaterial *mat) : SceneObject(mat)
	{
	}

    protected:
	virtual int getNumberOfTriangles()
	{
		return 1;
	}
	virtual std::vector<GLfloat> getVertexData()
	{
		std::vector<GLfloat> data{ -1.0f, -1.0f, 0.0f, 1.0f, -1.0f,
					   0.0f,  0.0f,  1.0f, 0.0f };
		return data;
	}

	virtual std::vector<GLfloat> getNormalsData()
	{
		return std::vector<GLfloat>();
	}

	virtual std::vector<GLfloat> getUvData()
	{
		std::vector<GLfloat> data{
			0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f,
		};
		return data;
	}
};
