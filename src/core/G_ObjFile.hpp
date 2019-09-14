#pragma once
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include "glm/glm.hpp"
using namespace std;
using namespace glm;

struct ObjFacePoint {
	unsigned int index;
	unsigned int normalIndex;
	unsigned int textureIndex;
};

struct ObjFace {
	ObjFacePoint first;
	ObjFacePoint second;
	ObjFacePoint third;
};

class G_ObjFile {
    public:
	vector<vec4> v;
	vector<vec3> vt;
	vector<vec3> vn;
	vector<vector<unsigned int> > g;
	vector<ObjFace> f;
	const char *path;
	G_ObjFile(const char *filePath) : path(filePath)
	{
	}

	bool loadFile()
	{
    return parse_file();
	}

    private:
	bool parse_file()
	{
    printf("Loading OBJ file %s...\n", path);
		FILE *file = fopen(path, "r");
		if (file == NULL) {
			printf("Impossible to open the file !\n");
			getchar();
			return false;
		}
		while (1) {
			char lineHeader[128];
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) {
        break;
			}
			if (strcmp(lineHeader, "v") == 0) {
				vec4 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x,
				       &vertex.y, &vertex.z);
				v.push_back(vertex);
			} else if (strcmp(lineHeader, "vt") == 0) {
				vec3 uvw;
				fscanf(file, "%f %f %f\n", &uvw.x, &uvw.y,
				       &uvw.z);
				vt.push_back(uvw);
			} else if (strcmp(lineHeader, "vn") == 0) {
				vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x,
				       &normal.y, &normal.z);
				vn.push_back(normal);
			} else if (strcmp(lineHeader, "f") == 0) {
				ObjFace face;
				int matches =
					fscanf(file,
					       "%d/%d/%d %d/%d/%d %d/%d/%d\n",
					       &face.first.index,
					       &face.first.textureIndex,
					       &face.first.normalIndex,
					       &face.second.index,
					       &face.second.textureIndex,
					       &face.second.normalIndex,
					       &face.third.index,
					       &face.third.textureIndex,
					       &face.third.normalIndex);
				f.push_back(face);
				add_face_to_last_group();
			} else {
				char nb[1000];
				fgets(nb, 1000, file);
			}
		}
    return true;
	}

	void create_group(FILE *file)
	{
		g.push_back(vector<unsigned int>());
	}

	void add_face_to_last_group()
	{
		int size = g.size();
		int faceSize = f.size();
		if (size > 0 && faceSize > 0) {
			g[size - 1].push_back(faceSize - 1);
		}
	}
};
