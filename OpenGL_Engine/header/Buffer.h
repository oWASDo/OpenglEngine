#pragma once
#include <vector>
#include "GraphicHeader.h"

class Buffer
{
public:
	Buffer(float buffer[], GLuint sizeOfBuffer, GLuint countStride, GLuint index);
	GLuint GenerateBuffer();

	GLuint Bind(GLuint index);


	GLuint GetBufferSize();
	GLuint GetStride();
	~Buffer();

private:
	GLuint bufferIndex;
	std::vector<float> bufferPointer;
	GLuint index;
	GLuint stride;

};
