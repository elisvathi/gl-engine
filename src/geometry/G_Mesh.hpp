#pragma once
#include <glm/glm.hpp>
#include "G_Vertex_Collection.hpp"
#include "G_Triangle.hpp"
#include "G_Vertex.hpp"
#include "../core/G_ObjFile.hpp"
#include "../core/G_Structs.hpp"
#include <vector>
using namespace glm;
using namespace std;

int max(int a, int b){
  return a > b ? a : b;
}

class G_Mesh {
    public:

	G_Vertex_Collection vertices;
	vector<G_Triangle> triangles;

  G_Mesh(){}

  vector<VectorData> get_vector_data(){
    vector<VectorData> returnValue;
    auto vertices = get_all_vertices();
    auto uvs = get_all_uvs();
    auto normals = get_normals();
    int totalSize = get_number_of_triangles() * 3;
    for(int i = 0; i < totalSize; i++) {
      VectorData item = {};
      item.position = vertices[i];
      item.normal = normals[i];
      item.uv = uvs[i];
      returnValue.push_back(item);
    }
    return returnValue;
  }

	vector<vec3> get_all_vertices()
	{
		vector<G_Vertex> all = get_vertices();
		vector<vec3> return_value;
		for (int i = 0; i < int(triangles.size()); i++) {
			auto t = triangles[i];
			return_value.push_back(all[t[0]].position);
			return_value.push_back(all[t[1]].position);
			return_value.push_back(all[t[2]].position);
		}
		return return_value;
	}

	vector<vec2> get_all_uvs()
	{
		vector<vec2> return_value;
		for (int i = 0; i < int(triangles.size()); i++) {
			auto t = triangles[i];
			return_value.push_back(t.first_uv);
			return_value.push_back(t.second_uv);
			return_value.push_back(t.third_uv);
		}
		return return_value;
	}

	virtual vector<vec3> get_normals(bool smooth = true)
	{
    if(smooth){
      return get_normals_smooth();
    }
    return get_normals_no_smooth();
	}

  int get_number_of_triangles(){
    return int(triangles.size());
  }
protected:

  virtual vector<vec3> get_normals_smooth(){
		vector<vec3> total_normals = get_total_normals();
		vector<vec3> return_value;
		for (int i = 0; i < int(triangles.size()); i++) {
			auto t = triangles[i];
			return_value.push_back(total_normals[t[0]]);
			return_value.push_back(total_normals[t[1]]);
			return_value.push_back(total_normals[t[2]]);
		}
		return return_value;
  }

  virtual vector<vec3> get_normals_no_smooth(){
		vector<vec3> return_value;
		for (int i = 0; i < int(triangles.size()); i++) {
			auto t = triangles[i];
      return_value.push_back(t.get_normal(&vertices));
      return_value.push_back(t.get_normal(&vertices));
      return_value.push_back(t.get_normal(&vertices));
		}
		return return_value;
  }

  virtual void add_polygon(vector<int> inds){
    if(inds.size()<3) { return;}
    for(int i = 1; i < int(inds.size()) - 1; i++){
      triangles.push_back(G_Triangle(inds[0], inds[i], inds[i+1]));
    }
  }

    private:

	vector<G_Vertex> get_vertices()
	{
		return vertices.vertices;
	}

	vector<vec3> get_total_normals()
	{
		vector<vec3> normals;
		for (int i = 0; i < int(vertices.vertices.size()); i++) {
			normals.push_back(get_smoothed_normal_by_index(i));
		}
		return normals;
	}

	vec3 get_smoothed_normal_by_index(int index)
	{
		vec3 initial = vec3(0, 0, 0);
		for (int i = 0; i < int(triangles.size()); i++) {
			G_Triangle t = triangles[i];
			if (t.contains_index(index)) {
				initial = initial + t.get_normal(&vertices);
			}
		}
		return normalize(initial);
	}
};

class G_ObjMesh: public G_Mesh {
public:
  G_ObjMesh(const char* path) {
    build_obj(path);
  }
private:
  void build_obj(const char* path){
    auto f = G_ObjFile(path);
    if(f.loadFile()){
      for(ulong i = 0; i < f.v.size(); i++ ){
        vec4 v = f.v[i];
        vertices.add_vertex(vec3(v.x, v.y, v.z));
      }
      for(ulong i = 0; i < f.f.size(); i++ ){
        ObjFace face = f.f[i];
        G_Triangle triangle(face.first.index - 1, face.second.index - 1, face.third.index - 1);
        if(f.vt.size() > 0) {
          int firstIndex = max(0, face.first.textureIndex - 1);
          int secondIndex = max(0, face.second.textureIndex - 1);
          int thirdIndex = max(0, face.third.textureIndex - 1);
          auto first_uv = f.vt[firstIndex];
          auto second_uv = f.vt[secondIndex];
          auto third_uv = f.vt[thirdIndex];
          triangle.first_uv = vec2(first_uv.x, first_uv.y);
          triangle.second_uv = vec2(second_uv.x, second_uv.y);
          triangle.third_uv = vec2(third_uv.x, third_uv.y);
        }
        triangles.push_back(triangle);
      }
    }
  }
};

class G_Box_Mesh: public G_Mesh {

public:

  G_Box_Mesh(vec3 pos, float sx, float sy, float sz): G_Mesh() {
    build_box(pos, sx, sy, sz);
  }
private:

  void build_box(vec3 center, float sx = 1, float sy = 1, float sz = 1){
    float hx = sx / 2.0f;
    float hy = sy / 2.0f;
    float hz = sz / 2.0f;

    vertices.add_vertex( center + vec3(hx, hy, hz));
    vertices.add_vertex( center + vec3(-hx, hy, hz));
    vertices.add_vertex( center + vec3(-hx, -hy, hz));
    vertices.add_vertex( center + vec3(hx, -hy, hz));

    vertices.add_vertex( center + vec3(hx, hy, -hz));
    vertices.add_vertex( center + vec3(-hx, hy, -hz));
    vertices.add_vertex( center + vec3(-hx, -hy, -hz));
    vertices.add_vertex( center + vec3(hx, -hy, -hz));

    add_polygon(vector<int>{0, 1, 2, 3});
    add_polygon(vector<int>{4, 5, 6, 7});

    add_polygon(vector<int>{0, 1, 5, 4});
    add_polygon(vector<int>{2, 3, 7, 6});

    add_polygon(vector<int>{0, 3, 7, 4});
    add_polygon(vector<int>{1, 2, 6, 5});
  }
};

class G_Cube_Mesh: public G_Box_Mesh{
public:
  G_Cube_Mesh(vec3 pos, float size): G_Box_Mesh(pos, size, size, size){}
};


