#pragma once
#include "GraphicHeader.h"
#include <vector>

using namespace std;

static vector<const char*> shaderPathList;
static vector<GLuint> shaderIndexList;

class ShaderList
{
public:
	ShaderList() {

	}
	~ShaderList() {

	}
	static void Add(const char* path, GLuint shaderIndex) {

		auto it = find(shaderPathList.begin(), shaderPathList.end(), path);
		if (it != shaderPathList.end()) {}
		else {
			shaderPathList.push_back(path);
			shaderIndexList.push_back(shaderIndex);
		}


	}
	static bool Exist(const char* path, GLuint& shaderIndex) {

		auto it = find(shaderPathList.begin(), shaderPathList.end(), path);
		if (it != shaderPathList.end()) {
			shaderIndex = shaderIndexList[distance(shaderPathList.begin(), it)];
			return true;
		}
		else {
			return false;
		}
	}

private:

};
