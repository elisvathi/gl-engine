#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "G_Utils.hpp"
#include "G_Shader.hpp"
#include "G_Node.hpp"
#include "G_Camera.hpp"
#include <vector>
#include <string>
#include "../geometry/G_Mesh.hpp"
#include "G_Light.hpp"
#include "G_ObjFile.hpp"
using namespace glm;
using namespace std;


class G_Object : public G_Node {
public:
  G_Shader *shader;
  G_Mesh *mesh;
  GLuint vertexBufferId;
  GLuint vertexArrayId;

	G_Object(G_Shader *mat, G_Mesh *m) : G_Node(), shader(mat), mesh(m)
	{
	}

  void build_object() {
    auto data= mesh->get_vector_data();
    for(int i = 0; i < int(data.size()); i++){
      data[i].color = shader->get_color(i);
    }
    uploadVertexData(shader->programID, data, vertexArrayId, vertexBufferId);
  }

  void draw_object(G_Camera* camera, G_Light* light) {
    GLuint texture;
    bool hasTexture = shader->get_texture(texture);
    drawVertexdata(shader->programID,
                   vertexBufferId,
                   texture,
                   hasTexture,
                   camera->get_vp_matrix(),
                   get_object_matrix(),
                   mesh->get_number_of_triangles(),
                   light->position,
                   light->direction,
                   light->color ,
                   camera->get_direction());
  }
};
