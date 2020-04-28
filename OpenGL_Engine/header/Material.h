#pragma once
#include <memory>
#include <vector>
#include "Shader.h"
#include "Buffer.h"
#include "Uniform.h"
#include "Texture.h"

using namespace std;

struct UniformElement
{
	const char* name;
	int elementNumber;
	UnifromType type;
};


class Material {

public:

	//Base
	Material(std::string fullShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber);
	Material(std::string verteShader, std::string fragmentShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber);
	Material(const char* vertexShaderPath, const char* fragmentShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber);
	Material(const char* fullShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber);

	//Index Buffer
	Material(std::string fullShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, GLuint indexBuffer[], GLuint indexBufferNumElement);
	Material(std::string verteShader, std::string fragmentShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, GLuint indexBuffer[], GLuint indexBufferNumElement);
	Material(const char* vertexShaderPath, const char* fragmentShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, GLuint indexBuffer[], GLuint indexBufferNumElement);
	Material(const char* fullShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, GLuint indexBuffer[], GLuint indexBufferNumElement);

	//Uniform element
	Material(std::string fullShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum);
	Material(std::string verteShader, std::string fragmentShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum);
	Material(const char* vertexShaderPath, const char* fragmentShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum);
	Material(const char* fullShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum);

	//both of them
	Material(std::string fullShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum, GLuint indexBuffer[], GLuint indexBufferNumElement);
	Material(std::string verteShader, std::string fragmentShader, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum, GLuint indexBuffer[], GLuint indexBufferNumElement);
	Material(const char* vertexShaderPath, const char* fragmentShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum, GLuint indexBuffer[], GLuint indexBufferNumElement);
	Material(const char* fullShaderPath, Buffer buffer[], GLuint bufferNum, Texture texs[], GLuint textureNumber, UniformElement uniElem[], GLuint uniformNum, GLuint indexBuffer[], GLuint indexBufferNumElement);


	void Use();

	void Draw();

	void UseAndDraw();

	void ChangeUniformFloat(GLuint modifier, float f1, float f2 = 0, float f3 = 0, float f4 = 0, bool bind = true) {
		if (bind)
		{
			Use();
		}
		for (GLuint i = 0; i < uniforms.size(); i++) {
			if (i == modifier) {
				uniforms[i]->Update(FromFloatToDatas(f1, f2, f3, f4));
			}
		}
	}
	void ChangeUniformFloatFromName(const char* uniformName, float f1, float f2 = 0, float f3 = 0, float f4 = 0, bool bind = true) {
		if (bind)
			Use();

		for (GLuint i = 0; i < uniforms.size(); i++) {
			if (uniforms[i]->GetName() == uniformName) {
				uniforms[i]->Update(FromFloatToDatas(f1, f2, f3, f4));
			}
		}
	}

	void ChangeUniformInt(GLuint modifier, int i1, int i2 = 0, int i3 = 0, int i4 = 0, bool bind = true) {
		if (bind)
		{
			Use();
		}
		for (GLuint i = 0; i < uniforms.size(); i++) {
			if (i == modifier) {
				uniforms[i]->Update(FromIntToDatas(i1, i2, i3, i4));

			}
		}
	}
	void ChangeUniformIntFromName(const char* uniformName, int i1, int i2 = 0, int i3 = 0, int i4 = 0, bool bind = true) {
		if (bind)
			Use();

		for (GLuint i = 0; i < uniforms.size(); i++) {
			std::string name = uniforms[i]->GetName();

			if (name.compare(uniformName) == 0) {
				uniforms[i]->Update(FromIntToDatas(i1, i2, i3, i4));

			}
		}
	}

	void ChangeUniformDouble(GLuint modifier, double d1, double d2 = 0, double d3 = 0, double d4 = 0, bool bind = true) {
		if (bind)
		{
			Use();
		}
		for (GLuint i = 0; i < uniforms.size(); i++) {
			if (i == modifier) {
				uniforms[i]->Update(FromDoubleToDatas(d1, d2, d3, d4));

			}
		}
	}
	void ChangeUniformDoubleFromName(const char* uniformName, double d1, double d2 = 0, double d3 = 0, double d4 = 0, bool bind = true) {
		if (bind)
			Use();

		for (GLuint i = 0; i < uniforms.size(); i++) {
			if (uniforms[i]->GetName() == uniformName)
				uniforms[i]->Update(FromDoubleToDatas(d1, d2, d3, d4));

		}
	}



	~Material();
private:
	void GenerateBufferList(Buffer buffer[], GLuint bufferNum);

	void GenerateBufferIndex(GLuint indexBuffer[], GLuint indexBufferNumElement);

	void AddImages(Texture texture[], GLuint arrayTextureNum);
	
	void GenUniform(UniformElement uniElem[], GLuint uniformNum) {

		for (GLuint i = 0; i < uniformNum; i++)
		{
			float arr[4] = { 0.0f,0.0f,1.0f,0.0f };
			UniformFloat* uf1;

			int arr2[4] = { 0,0,0,0 };
			UniformInt* uf2;

			double arr3[4] = { 0.0,0.0,0.0,0.0 };
			UniformDouble* uf3;
			
			switch (uniElem[i].type)
			{
			case UnifromType::Float:
				uf1 = new UniformFloat(matShader->GetShaderIndex(), uniElem[i].name, uniElem[i].elementNumber, arr);
				uniforms.push_back(uf1);
				break;

			case UnifromType::Int:
				uf2 = new UniformInt(matShader->GetShaderIndex(), uniElem[i].name, uniElem[i].elementNumber, arr2);
				uniforms.push_back(uf2);
				break;

			case UnifromType::Double:
				uf3 = new UniformDouble(matShader->GetShaderIndex(), uniElem[i].name, uniElem[i].elementNumber, arr3);
				uniforms.push_back(uf3);
				break;
			}
			
		}
	}


	std::shared_ptr<Shader> matShader;
	std::vector<GLuint> indexes;
	std::vector<GLuint> buffersIndex;
	std::vector<Uniform*> uniforms;
	std::vector<Texture> textures;

	GLuint indexBufferPointer;
	GLuint vao;
	GLuint triangleToDraw;

};
