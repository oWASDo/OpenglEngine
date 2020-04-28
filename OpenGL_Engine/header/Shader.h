#pragma once
#include "GraphicHeader.h"
#include <string>
#include <list>
#include <vector>
#include "FileReader.h"
#include <iostream>
#include <fstream>

struct ShadersBlob
{
	std::string vertexBlob;
	std::string fragmentBlob;
	std::string geometryBlob;

};

class Shader
{
public:
	/// <summary>
	/// Generate shader from a file already readed.
	/// Shader are splitted
	/// </summary>
	Shader(std::string& vertexShader, std::string& fragmentShader);

	/// <summary>
	/// Generate shader from a file already readed.
	/// Insert compleate shader
	/// </summary>
	Shader(std::string& completeShader);

	/// <summary>
	/// Generate shader from a file.
	/// Insert compleate shader
	/// </summary>
	Shader(const char* filePath);

	/// <summary>
	/// Generate shader from a file.
	/// Shader are splitted
	/// </summary>
	Shader(const char* vertexShader, const char*fragmentShader);

	~Shader();

private:

	GLuint CompileShader(unsigned int type, const std::string& source);
	
	void generateShader(std::string& vertexShaderPath, std::string& fragmentShaderPath);
	
	void generateShader(std::string& completeShader);

	void generateShaderFromPath(const char* filePath);

	void generateShaderFromPath(const char* vertexFilePath, const char* fragmentFilePath);


	void composeShader(GLuint vs, GLuint fs);

	//divide shaders
	void reedAndDiveidShadersSource(std::string filePath);
	void dividShadersSource(std::string file);



private:

	ShadersBlob blobs;
	GLuint mainShader;
	GLuint buffer;

public:
	void Bind();
	GLuint GetShaderIndex() {

		return mainShader;
	}
private:
};

