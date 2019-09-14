#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stb_image.h"
#include "G_Structs.hpp"
#include "glm/glm.hpp"
using namespace std;
using namespace glm;

template <class T> void modifyBuffer(GLuint &bufferId, vector<T> data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), &data.front(),
		     GL_STATIC_DRAW);
}

template <class T> void createArrayBuffer(GLuint &bufferId, vector<T> data)
{
	glGenBuffers(1, &bufferId);
	modifyBuffer(bufferId, data);
}

void modifyTexture(GLuint &textureId, const char *path)
{
	int width, height, nn;
	unsigned char *textureData = stbi_load(path, &width, &height, &nn, 0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR,
		     GL_UNSIGNED_BYTE, textureData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void createTexture(GLuint &textureId, const char *path)
{
	glGenTextures(1, &textureId);
	modifyTexture(textureId, path);
}

GLuint loadTexture(const char *path)
{
	GLuint textureId;
	createTexture(textureId, path);
	return textureId;
}

float map(float x, float a1, float b1, float a2, float b2)
{
	float rap = (x - a1) / (b1 - a1);
	return a2 + rap * (b2 - a2);
}

void uploadVertexData(GLuint programId, vector<VectorData> data,
		      GLuint &vertexArrayId, GLuint &arrayBufferId)
{
	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);
	createArrayBuffer(arrayBufferId, data);
}

void drawVertexdata(GLuint programId, GLuint arrayBufferId, GLuint texture,
		    bool hasTexture, mat4 cameraMatrix, mat4 objectMatrix,
		    int numberOfTriangles, vec3 lightPos, vec3 lightDirection,
		    vec3 lightColor, vec3 cameraDirection)
{
	int attribCount = 4;
	glUseProgram(programId);

	// Apply camera matrix
	mat4 totalMvp = cameraMatrix * objectMatrix;
	GLuint MatrixID = glGetUniformLocation(programId, "G_Mvp");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &totalMvp[0][0]);
	GLuint CameraDirectionId =
		glGetUniformLocation(programId, "G_CameraDirection");
	glUniform3f(CameraDirectionId, cameraDirection.x, cameraDirection.y,
		    cameraDirection.z);

	// Apply light
	GLuint LightPositionId =
		glGetUniformLocation(programId, "G_LightPositionId");
	GLuint LightColorId = glGetUniformLocation(programId, "G_LightColor");
	GLuint LightDirectionId =
		glGetUniformLocation(programId, "G_LightDirection");
	glUniform3f(LightPositionId, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(LightColorId, lightColor.x, lightColor.y, lightColor.z);
	glUniform3f(LightDirectionId, lightDirection.x, lightDirection.y,
		    lightDirection.z);

	// Apply texture
	GLuint enabled = glGetUniformLocation(programId, "G_EnableTexture");
	if (hasTexture) {
		GLuint TextureID = glGetUniformLocation(programId, "G_Texture");
		glUniform1i(enabled, 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(TextureID, texture);
		glUniform1i(TextureID, 0);
	} else {
		glUniform1i(enabled, 0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, arrayBufferId);
	for (int j = 0; j < attribCount; j++) {
		int size = j == 3 ? 2 : 3;
		glEnableVertexAttribArray(j);
		glVertexAttribPointer(j, size, GL_FLOAT, GL_FALSE,
				      sizeof(VectorData),
				      (void *)(j * sizeof(vec3)));
	}
	glDrawArrays(GL_TRIANGLES, 0, numberOfTriangles * 3);

	for (int j = 0; j < attribCount; j++) {
		glDisableVertexAttribArray(j);
	}
}
