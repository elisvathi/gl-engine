#pragma once
#include <GL/glew.h>
#include <vector>
#include "G_Structs.hpp"
using namespace std;
class G_Pipeline {
    public:
	G_Pipeline *createVertexArray(GLuint &id)
	{
		return this;
	}

	G_Pipeline *createVertexBuffer(GLuint arrayId, GLuint &bufferId)
	{
		return this;
	}

	G_Pipeline *uploadVertexData(GLuint bufferId, vector<VectorData> data)
	{
		return this;
	}
};
