#pragma once
#include "View.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "SceneMaterial.hpp"
#include "SceneObject.hpp"
#include "ObjLoader.hpp"
#include <iostream>
#include <vector>
class ExternalObj : public SceneObject {
    private:
	std::vector<vec3> vertices;
	std::vector<vec2> uv;
	std::vector<vec3> normals;

    public:
	ExternalObj(const char *path, SceneMaterial *mat) : SceneObject(mat)
	{
		if (!loadOBJ(path, vertices, uv, normals)) {
			std::cerr << "Could not load obj" << std::endl;
		}
	}

    protected:
	virtual int getNumberOfTriangles()
	{
		return int(vertices.size() / 3);
	}
	virtual std::vector<GLfloat> getVertexData()
	{
		std::vector<GLfloat> data;
		for (int i = 0; i < int(vertices.size()); i++) {
			data.push_back(vertices[i].x);
			data.push_back(vertices[i].y);
			data.push_back(vertices[i].z);
		}
		return data;
	}

	virtual std::vector<GLfloat> getNormalsData()
	{
		std::vector<GLfloat> data;
		for (int i = 0; i < int(normals.size()); i++) {
			data.push_back(normals[i].x);
			data.push_back(normals[i].y);
			data.push_back(normals[i].z);
		}
		return data;
	}

	virtual std::vector<GLfloat> getUvData()
	{
		std::vector<GLfloat> data;
		for (int i = 0; i < int(uv.size()); i++) {
			data.push_back(uv[i].x);
			data.push_back(uv[i].y);
		}
		return data;
	}
};
