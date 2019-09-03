#pragma once
#include <vector>
#include "G_Triangle.hpp"
using namespace std;
class G_Smoothing_Group {
    public:
	G_Smoothing_Group()
	{
	}
	vector<int> indices;

    private:
	bool has(int index)
	{
		for (int i = 0; i < int(indices.size()); i++) {
			if (indices[i] == index) {
				return true;
			}
			return false;
		}
	}

	bool neighbourTriangles(int index, vector<G_Triangle> triangles,
				vector<int> *inds)
	{
		bool found = false;
		G_Triangle current = triangles[index];
		for (int i = 0; i < int(indices.size()); i++) {
			if (indices[i] == index) {
				found = true;
			}
			if (i != index) {
				if (current.share_same_vertices(triangles[i])) {
					inds->push_back(i);
				}
			}
		}
		return found;
	}
};
