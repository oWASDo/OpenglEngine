#include "Buffer.h"

Buffer::Buffer(float buffer[], GLuint sizeOfBuffer, GLuint countStride, GLuint index)
{

	sizeOfBuffer = sizeOfBuffer / sizeof(float);
	stride = countStride;
	this->index = index;

	for (GLuint i = 0; i < sizeOfBuffer; i++)
	{
		bufferPointer.push_back(buffer[i]);
	}
}

GLuint Buffer::GenerateBuffer()
{
	glGenBuffers(1, &bufferIndex);
	glBindBuffer(GL_ARRAY_BUFFER, bufferIndex);
	glBufferData(GL_ARRAY_BUFFER, bufferPointer.size() * sizeof(float), bufferPointer.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, stride, GL_FLOAT, GL_FALSE, sizeof(float) * stride, 0);
	return bufferIndex;
}

GLuint Buffer::Bind(GLuint index)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferIndex);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, stride, GL_FLOAT, GL_FALSE, sizeof(float) * stride, 0);
	
	return 0;
}

GLuint Buffer::GetBufferSize()
{
	return bufferPointer.size();
}

GLuint Buffer::GetStride()
{
	return stride;
}

Buffer::~Buffer()
{
	bufferPointer.clear();
}
