#include "Material.h"

Material::Material(std::string fullShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber) {
	matShader = std::make_shared<Shader>(fullShader);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
}
Material::Material(std::string verteShader, std::string fragmentShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber) {
	matShader = std::make_shared<Shader>(verteShader, fragmentShader);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
}
Material::Material(const char * vertexShaderPath, const char * fragmentShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber) {
	matShader = std::make_shared<Shader>(vertexShaderPath, fragmentShaderPath);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
}
Material::Material(const char * fullShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber) {
	matShader = std::make_shared<Shader>(fullShaderPath);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
}

Material::Material(std::string fullShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, GLuint indexBuffer[], GLuint indexBufferNumElement) {
	matShader = std::make_shared<Shader>(fullShader);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
	GenerateBufferIndex(indexBuffer, indexBufferNumElement);
}
Material::Material(std::string verteShader, std::string fragmentShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, GLuint indexBuffer[], GLuint indexBufferNumElement) {
	matShader = std::make_shared<Shader>(verteShader, fragmentShader);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
	GenerateBufferIndex(indexBuffer, indexBufferNumElement);
}
Material::Material(const char * vertexShaderPath, const char * fragmentShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, GLuint indexBuffer[], GLuint indexBufferNumElement) {
	matShader = std::make_shared<Shader>(vertexShaderPath, fragmentShaderPath);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
	GenerateBufferIndex(indexBuffer, indexBufferNumElement);
}
Material::Material(const char * fullShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, GLuint indexBuffer[], GLuint indexBufferNumElement) {
	matShader = std::make_shared<Shader>(fullShaderPath);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
	GenerateBufferIndex(indexBuffer, indexBufferNumElement);

}

Material::Material(std::string fullShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum) {
	matShader = std::make_shared<Shader>(fullShader);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
	GenUniform(uniElem, uniformNum);
}
Material::Material(std::string verteShader, std::string fragmentShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum) {
	matShader = std::make_shared<Shader>(verteShader, fragmentShader);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
	GenUniform(uniElem, uniformNum);
}
Material::Material(const char * vertexShaderPath, const char * fragmentShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum) {
	matShader = std::make_shared<Shader>(vertexShaderPath, fragmentShaderPath);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
	GenUniform(uniElem, uniformNum);
}
Material::Material(const char * fullShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum) {
	matShader = std::make_shared<Shader>(fullShaderPath);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
	GenUniform(uniElem, uniformNum);

}

Material::Material(std::string fullShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum, GLuint indexBuffer[], GLuint indexBufferNumElement) {
	matShader = std::make_shared<Shader>(fullShader);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
	GenerateBufferIndex(indexBuffer, indexBufferNumElement);
	GenUniform(uniElem, uniformNum);
}
Material::Material(std::string verteShader, std::string fragmentShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum, GLuint indexBuffer[], GLuint indexBufferNumElement) {
	matShader = std::make_shared<Shader>(verteShader, fragmentShader);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
	GenerateBufferIndex(indexBuffer, indexBufferNumElement);
	GenUniform(uniElem, uniformNum);
}
Material::Material(const char * vertexShaderPath, const char * fragmentShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum, GLuint indexBuffer[], GLuint indexBufferNumElement) {
	matShader = std::make_shared<Shader>(vertexShaderPath, fragmentShaderPath);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
	GenerateBufferIndex(indexBuffer, indexBufferNumElement);
	GenUniform(uniElem, uniformNum);

}
Material::Material(const char * fullShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum, GLuint indexBuffer[], GLuint indexBufferNumElement) {
	matShader = std::make_shared<Shader>(fullShaderPath);
	AddImages(texs, textureNumber);
	GenerateBufferList(buffer, bufferNum);
	GenerateBufferIndex(indexBuffer, indexBufferNumElement);
	GenUniform(uniElem, uniformNum);
}

void Material::AddImages(Texture texture[], GLuint arrayTextureNum) {

	for (int i = 0; i < arrayTextureNum; i++) {
		textures.push_back(texture[i]);
	}
}


void Material::Use()
{
	matShader->Bind();
	glBindVertexArray(vao);
	for (int i = 0; i < textures.size(); i++)
	{

		textures[i].Bind(i, matShader->GetShaderIndex());
	}
	if (indexBufferPointer != 0) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferPointer);

	}
}

void Material::Draw()
{
	for (int i = 0; i < uniforms.size(); i++)
	{
		uniforms[i]->SubUpdate();
	}
	if (indexBufferPointer == 0)
	{
		glDrawArrays(GL_TRIANGLES, 0, triangleToDraw);

	}
	else
	{
		glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, nullptr);
	}
}

void Material::UseAndDraw()
{
	Use();
	Draw();
}

Material::~Material()
{
	matShader.~shared_ptr();
	indexes.clear();
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(buffersIndex.size(), &buffersIndex[0]);

	for (GLuint i = 0; i < uniforms.size(); i++) {
		delete(uniforms[i]);
	}

	std::cout << "destroy" << std::endl;
}

void Material::GenerateBufferList(Buffer buffer[], GLuint bufferNum)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	triangleToDraw = buffer[0].GetBufferSize() / buffer[0].GetStride();
	for (size_t i = 0; i < bufferNum; i++) {
		GLuint bufferIndex = buffer[i].GenerateBuffer();
		buffersIndex.push_back(bufferIndex);
	}
}

void Material::GenerateBufferIndex(GLuint indexBuffer[], GLuint indexBufferNumElement)
{
	indexBufferPointer = 0;
	if (indexBuffer == nullptr)
		return;

	for (size_t i = 0; i < indexBufferNumElement; i++) {
		indexes.push_back(indexBuffer[i]);
	}

	glGenBuffers(1, &indexBufferPointer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferPointer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLuint), indexes.data(), GL_STATIC_DRAW);
}
