#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
void readShader(const char* path, std::string& data) {
  std::ifstream fileStream(path, std::ios::in);
  if(fileStream.is_open()){
    std::stringstream sstr;
    sstr << fileStream.rdbuf();
    data = sstr.str();
    fileStream.close();
  }else{
    std::cout << "Impossible to open " << path << std::endl;
    getchar();
  }
}

void checkShaderCorrectness(GLuint shader){
  GLint result = GL_FALSE;
  int InfoLogLength;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if(InfoLogLength > 0){
    std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(shader, InfoLogLength, nullptr, &ShaderErrorMessage[0]);
    std::cout << &ShaderErrorMessage[0] << std::endl;
  }
}

void compileShader(const char* path, GLuint shader){
  std::string data;
  readShader(path, data);
  const char* datacstr = data.c_str();
  glShaderSource(shader, 1, &datacstr, nullptr);
  std::cout << "Compiling shader " << path << std::endl;
  glCompileShader(shader);
  checkShaderCorrectness(shader);
}

void checkProgramCorrectness(GLuint program){
  GLint result = GL_FALSE;
  int InfoLogLength;
  glGetProgramiv(program, GL_LINK_STATUS, &result);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if(InfoLogLength > 0){
    std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
    glGetProgramInfoLog(program, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
    std::cout << &ProgramErrorMessage[0] << std::endl;
  }
}

void detachShaders(GLuint program, GLuint vertex, GLuint fragment){
  glDetachShader(program, vertex);
  glDetachShader(program, fragment);
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

GLuint linkProgram(GLuint vertex, GLuint fragment){
  std::cout << "Linking program" << std::endl;
  GLuint programID = glCreateProgram();
  glAttachShader(programID, vertex);
  glAttachShader(programID, fragment);
  glLinkProgram(programID);
  checkProgramCorrectness(programID);
  detachShaders(programID, vertex, fragment);
  return programID;
}

GLuint buildProgram(const char* vertex_path,const char* fragment_path) {
  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  compileShader(vertex_path, vertexShaderID);
  compileShader(fragment_path, fragmentShaderID);
  return linkProgram(vertexShaderID, fragmentShaderID);
}
