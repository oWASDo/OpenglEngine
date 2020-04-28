#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "GraphicHeader.h"

enum UnifromType
{
	Float,
	Int,
	Double
};
struct Datas
{
	unsigned char Data[32];
};

class Uniform
{
public:
	Uniform(GLuint shader, const char* uniformName, int elemNumber) {
		GLint tipe = glGetUniformLocation(shader, uniformName);
		if (tipe == -1) {
			std::cout << "invalid Unifrom" << std::endl;
			//exit(-5); 
		}
		
		uniformLocation = tipe;
		name.append(uniformName);
		elementNuber = elemNumber;
	}
	~Uniform() {
	}

	virtual void Update(Datas data) = 0;
	virtual void SubUpdate() = 0;

	std::string GetName() {
		return name;
	}
protected:
	std::string name;
	virtual void Abstraction() = 0;

	virtual void IplicitCast() {

	}


	GLuint elementNuber;
	GLuint uniformLocation;
	GLuint type;
	GLuint typeSize;
	GLuint elementsNumber;
	Datas datas;
	bool update;

private:
};

class UniformFloat : public Uniform {

public:
	UniformFloat(GLuint shader, const char* name, int elemNumber, float initialDatas[]) :Uniform(shader, name, elemNumber) {
		elementsNumber = elemNumber;
		typeSize = sizeof(float);
		type = 2;
		for (GLuint i = 0; i < elementsNumber; i++) {
			memcpy(datas.Data + (i * typeSize), &initialDatas[i], typeSize);
		}
		
	}

	void Abstraction() {}
	void Update(Datas data)
	{
		if (memcmp(&data.Data[0], &datas.Data[0], sizeof(char) * 32) != 0)
		{
			for (GLuint i = 0; i < elementsNumber; i++)
			{
				memcpy(datas.Data + (i * typeSize), &data.Data[i* typeSize], typeSize);
			}
			SubUpdate();
		}
	}
protected:
	void SubUpdate() {
		switch (elementsNumber) {

			float f1, f2, f3, f4;
		case 1:
			memcpy(&f1, &datas.Data[0], typeSize);
			glUniform1f(uniformLocation, f1);
			break;
		case 2:
			memcpy(&f1, &datas.Data[0], typeSize);
			memcpy(&f2, &datas.Data[typeSize], typeSize);
			glUniform2f(uniformLocation, f1, f2);
			break;
		case 3:
			memcpy(&f1, &datas.Data[0], typeSize);
			memcpy(&f2, &datas.Data[typeSize], typeSize);
			memcpy(&f3, &datas.Data[2 * typeSize], typeSize);
			glUniform3f(uniformLocation, f1, f2, f3);
			break;
		case 4:
			memcpy(&f1, &datas.Data[0], typeSize);
			memcpy(&f2, &datas.Data[typeSize], typeSize);
			memcpy(&f3, &datas.Data[2 * typeSize], typeSize);
			memcpy(&f4, &datas.Data[3 * typeSize], typeSize);
			glUniform4f(uniformLocation, f1, f2, f3, f4);
			break;

		}
	}


};
class UniformInt : public Uniform {

public:
	UniformInt(GLuint shader, const char* name, int elemNumber, int initialDatas[]) :Uniform(shader, name, elemNumber) {
		elementsNumber = elemNumber;
		typeSize = sizeof(int);
		type = 1;
		for (GLuint i = 0; i < elementsNumber; i++) {
			memcpy(datas.Data + (i * typeSize), &initialDatas[i], typeSize);
		}
		
	}
	void Abstraction() {}
	void Update(Datas data) {
		if (memcmp(&data.Data[0], &datas.Data[0], sizeof(char) * 32) != 0) {
			for (GLuint i = 0; i < elementsNumber; i++)
			{
				memcpy(datas.Data + (i * typeSize), &data.Data[i* typeSize], typeSize);

			}
			SubUpdate();
		}
	}
protected:
	void SubUpdate() {
		switch (elementsNumber) {

			int i1, i2, i3, i4;
		case 1:
			memcpy(&i1, &datas.Data[0], typeSize);
			glUniform1i(uniformLocation, i1);
			break;
		case 2:
			memcpy(&i1, &datas.Data[0], typeSize);
			memcpy(&i2, &datas.Data[typeSize], typeSize);
			glUniform2i(uniformLocation, i1, i2);
			break;
		case 3:
			memcpy(&i1, &datas.Data[0], typeSize);
			memcpy(&i2, &datas.Data[typeSize], typeSize);
			memcpy(&i3, &datas.Data[2 * typeSize], typeSize);
			glUniform3i(uniformLocation, i1, i2, i3);
			break;
		case 4:
			memcpy(&i1, &datas.Data[0], typeSize);
			memcpy(&i2, &datas.Data[typeSize], typeSize);
			memcpy(&i3, &datas.Data[2 * typeSize], typeSize);
			memcpy(&i4, &datas.Data[3 * typeSize], typeSize);
			glUniform4i(uniformLocation, i1, i2, i3, i4);
			break;

		}
	}

private:
};
class UniformDouble : public Uniform {

public:
	UniformDouble(GLuint shader, const char* name, int elemNumber, double initialDatas[]) :Uniform(shader, name, elemNumber) {


		elementsNumber = elemNumber;
		typeSize = sizeof(double);
		type = 3;
		for (GLuint i = 0; i < elementsNumber; i++)
		{
			memcpy(datas.Data + (i * typeSize), &initialDatas[i], typeSize);
		}
	}

	void Abstraction() {}
	void Update(Datas data)
	{
		if (memcmp(&data.Data[0], &datas.Data[0], sizeof(char) * 32) != 0)
		{
			for (GLuint i = 0; i < elementsNumber; i++)
			{
				memcpy(datas.Data + (i * typeSize), &data.Data[i* typeSize], typeSize);

			}
			update = true;
		}
	}

protected:
	void SubUpdate() {
		if (update == true) {
			switch (elementsNumber) {

				double d1, d2, d3, d4;
			case 1:
				memcpy(&d1, &datas.Data[0], typeSize);
				glUniform1d(uniformLocation, d1);
				break;
			case 2:
				memcpy(&d1, &datas.Data[0], typeSize);
				memcpy(&d2, &datas.Data[typeSize], typeSize);
				glUniform2d(uniformLocation, d1, d2);
				break;
			case 3:
				memcpy(&d1, &datas.Data[0], typeSize);
				memcpy(&d2, &datas.Data[typeSize], typeSize);
				memcpy(&d3, &datas.Data[2 * typeSize], typeSize);
				glUniform3d(uniformLocation, d1, d2, d3);
				break;
			case 4:
				memcpy(&d1, &datas.Data[0], typeSize);
				memcpy(&d2, &datas.Data[typeSize], typeSize);
				memcpy(&d3, &datas.Data[2 * typeSize], typeSize);
				memcpy(&d4, &datas.Data[3 * typeSize], typeSize);
				glUniform4d(uniformLocation, d1, d2, d3, d4);
				break;
			}
			update = false;
		}
	}

private:
};

static Datas FromFloatToDatas(float f1, float f2 = 0, float f3 = 0, float f4 = 0) {
	Datas dat;
	for (int i = 1; i < 5; i++)
	{
		float f;
		switch (i)
		{
		case 1:
			f = f1; break;

		case 2:
			f = f2; break;

		case 3:
			f = f3; break;

		case 4:
			f = f4; break;
		}
		memcpy(&dat.Data[(i - 1) * sizeof(float)], &f, sizeof(float));
	}
	return dat;
}
static Datas FromIntToDatas(int i1, int i2, int i3, int i4) {
	Datas dat;
	for (int i = 1; i < 5; i++)
	{
		int in;
		switch (i)
		{
		case 1:
			in = i1; break;

		case 2:
			in = i2; break;

		case 3:
			in = i3; break;

		case 4:
			in = i4; break;
		}
		memcpy(&dat.Data[(i - 1) * sizeof(int)], &in, sizeof(int));
	}
	return dat;
}
static Datas FromDoubleToDatas(double d1, double d2, double d3, double d4) {
	Datas dat;
	for (int i = 1; i < 5; i++)
	{
		double d;
		switch (i)
		{
		case 1:
			d = d1; break;

		case 2:
			d = d2; break;

		case 3:
			d = d3; break;

		case 4:
			d = d4; break;
		}
		memcpy(&dat.Data[(i - 1) * sizeof(double)], &d, sizeof(double));
	}
	return dat;
}
