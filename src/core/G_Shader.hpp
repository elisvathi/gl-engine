#pragma once
#include <GL/glew.h>
#include "G_Shader_Utils.hpp"
#include "G_Utils.hpp"
#include <glm/glm.hpp>
#include <string>

using namespace std;
using namespace glm;

class G_Shader {
    public:
	GLuint programID;
	G_Shader(const char *vertex_path, const char *fragment_path)
	{
		programID = buildProgram(vertex_path, fragment_path);
	}

	virtual vec3 get_color() = 0;

	virtual vec3 get_color(int vertexIndex) = 0;

  virtual bool get_texture(GLuint &id) = 0;
	~G_Shader()
	{
		glDeleteProgram(programID);
	}
};
class G_TextureShader: public G_Shader {
public:
  GLuint texture;
	G_TextureShader(const char *texture_path)
		: G_Shader(string("assets/shaders/vertex.glsl").c_str(),
               string("assets/shaders/fragment.glsl").c_str())
	{
    texture = loadTexture(texture_path);
	}

	virtual vec3 get_color()
	{
		return vec3(0,0,0);
	}

  virtual bool get_texture(GLuint &id){
    id = texture;
    return true;
  }

	virtual vec3 get_color(int vertexIndex)
	{
		return vec3(0,0,0);
	}
};

class G_ColorShader : public G_Shader {
    public:
	vec3 color;
	G_ColorShader(vec3 col)
		: G_Shader(string("assets/shaders/vertex.glsl").c_str(),
			   string("assets/shaders/fragment.glsl").c_str()),
		  color(col)
	{
	}

  virtual bool get_texture(GLuint &id){
    return false;
  }

	virtual vec3 get_color()
	{
		return color;
	}

	virtual vec3 get_color(int vertexIndex)
	{
		return color;
	}
};
