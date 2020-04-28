#pragma once
#include "GraphicHeader.h"
#include <string>

class Texture
{
public:
	Texture(const std::string& path, const std::string& shaderTextureName);
	~Texture();

	void Bind(GLuint slot, GLuint shader);

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }

	std::string shaderTextureName;
private:
	GLuint textureID;
	std::string filePth;
	unsigned char* localBuffer;
	GLint width, height, BPP;
};