#pragma once
#include "View.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneMaterial.hpp"
#include "Utils.hpp"
#include <vector>
#include <string>

using namespace glm;
using namespace std;
class Node {
    public:
	Node(vec3 pos = vec3(0, 0, 0), vec3 sc = vec3(1.0f, 1.0f, 1.0f),
	     vec3 rot = vec3(0, 0, 0))
		: positionVector(pos), scaleVector(sc), rotationVector(rot)
	{
	}
	mat4 getObjectMatrix()
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

class SceneObject : public Node {
    public:
	SceneMaterial *material;
	GLuint vertexArrayId;
	GLuint vertexBufferId;
	GLuint colorbuffer;
	GLuint uvBuffer;
	GLuint TextureID;
	GLuint Texture;
	GLuint MatrixID;
	Camera *camera;

	SceneObject(SceneMaterial *mat) : Node(), material(mat)
	{
	}

	~SceneObject()
	{
		if (material != nullptr) {
			delete material;
		}
		glDeleteBuffers(1, &vertexBufferId);
		glDeleteVertexArrays(1, &vertexArrayId);
	}

	void buildBuffer(Camera *cam)
	{
		camera = cam;
		build();
		glUseProgram(material->programID);
		MatrixID = glGetUniformLocation(material->programID, "MVP");
		TextureID = glGetUniformLocation(material->programID,
						 "textureSampler");
		std::string path = "textures/uvtemplate.tga";
		Texture = loadTexture(path.c_str());
	}

	void applyMvp()
	{
		mat4 mvp = camera->getVpMatrix();
		mvp = mvp * getObjectMatrix();
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	}

	void draw()
	{
		glUseProgram(material->programID);
		applyMvp();
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		glVertexAttribPointer(0, //
				      3, // SIZE
				      GL_FLOAT, // TYPE
				      GL_FALSE, // NORMALIZED
				      0, // stride
				      (void *)0 // Array buffer offset
		);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(1, //
				      3, // SIZE
				      GL_FLOAT, // TYPE
				      GL_FALSE, // NORMALIZED
				      0, // stride
				      (void *)0 // Array buffer offset
		);

		// TEXTURE
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(TextureID, Texture);
		glUniform1i(TextureID, 0);

		// UV COORDS
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(2, //
				      2, // SIZE
				      GL_FLOAT, // TYPE
				      GL_FALSE, // NORMALIZED
				      0, // stride
				      (void *)0 // Array buffer offset
		);
		// DRAW
		glDrawArrays(GL_TRIANGLES, 0, getNumberOfTriangles() * 3);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

    private:
	void build()
	{
		glGenVertexArrays(1, &vertexArrayId);
		glBindVertexArray(vertexArrayId);
		createArrayBuffer(vertexBufferId, getVertexData());
		createArrayBuffer(colorbuffer, getColorData());
		createArrayBuffer(uvBuffer, getUvData());
		std::cout << "Building scene object" << std::endl;
	}

    protected:
	virtual int getNumberOfTriangles() = 0;
	virtual std::vector<GLfloat> getVertexData() = 0;
	virtual std::vector<GLfloat> getColorData()
	{
		vector<GLfloat> retValue;
		for (int i = 0; i < getNumberOfTriangles() * 3; i++) {
			vec3 color = material->getColor(i);
			retValue.push_back(color.x);
			retValue.push_back(color.y);
			retValue.push_back(color.z);
		}
		return retValue;
	};

	virtual std::vector<GLfloat> getNormalsData() = 0;

	virtual std::vector<GLfloat> getUvData() = 0;
	std::vector<GLfloat> getRandomColors()
	{
		std::vector<GLfloat> data;
		for (int i = 0; i < getNumberOfTriangles() * 3; i++) {
			data.push_back((GLfloat)drand48());
			data.push_back((GLfloat)drand48());
			data.push_back((GLfloat)drand48());
		}
		return data;
	}
};
