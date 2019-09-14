#pragma once
#include <GL/glew.h>
#include <vector>
using namespace std;


template <class T>
void modifyBuffer(GLuint &bufferId, vector<T> data) {
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), &data.front(), GL_STATIC_DRAW);
}

template <class T>
void createArrayBuffer(GLuint &bufferId, vector<T> data){
  glGenBuffers(1, &bufferId);
  modifyBuffer(bufferId, data);
}

void modifyTexture(GLuint &textureId, const char* path) {
  int width, height, nn;
  unsigned char *textureData;
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, textureData);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void createTexture(GLuint &textureId, const char* path){
  glGenTextures(1, &textureId);
  modifyTexture(textureId, path);
}

GLuint loadTexture(const char* path){
  GLuint textureId;
  createTexture(textureId, path);
  return textureId;
}

float map(float x, float a1, float b1, float a2, float b2){
  float rap = (x-a1)/ (b1-a1);
  return a2 + rap * (b2-a2);
}
