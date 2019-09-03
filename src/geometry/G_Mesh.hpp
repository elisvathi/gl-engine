#pragma once
#include <glm/glm.hpp>
#include "G_Vertex_Collection.hpp"
#include "G_Triangle.hpp"
#include "G_Vertex.hpp"
#include <vector>

using namespace glm;
using namespace std;
class G_Mesh {
    public:
	G_Vertex_Collection vertices;
	vector<G_Triangle> triangles;
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
		vector<G_Vertex> all = get_vertices();
		vector<vec2> return_value;
		for (int i = 0; i < int(triangles.size()); i++) {
			auto t = triangles[i];
			return_value.push_back(all[t[0]].UV);
			return_value.push_back(all[t[1]].UV);
			return_value.push_back(all[t[2]].UV);
		}
		return return_value;
	}

	vector<vec3> get_normals()
	{
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
