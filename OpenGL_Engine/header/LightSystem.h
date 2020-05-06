#pragma once
#include <vector>
#include "Vector.h"
#include "GraphicHeader.h"

enum LightType
{
	Direct,
	Point,
	Spot
};

class LightSystem
{
public:
	LightSystem()
	{
		LightListIndex = 0;
		glGenBuffers(1, &LightListIndex);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, LightListIndex);
		glBufferData(GL_SHADER_STORAGE_BUFFER, DirectLightStride, (void*)DirectLights.data(), GL_DYNAMIC_COPY);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 10, LightListIndex);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		DirectLights.push_back(0);
	}

	~LightSystem()
	{
	}
	int AddDirectLight(float intensity, Vector direction) {

		DirectNum++;
		DirectLights[0] = DirectNum;
		DirectLights.push_back(intensity);
		DirectLights.push_back(direction.x);
		DirectLights.push_back(direction.y);
		DirectLights.push_back(direction.z);

		return DirectNum - 1;
	}
	int AddPointLight() {

	}
	int AddSpotLight() {

	}

	void UpdateBuffer() {

		std::vector<float> Lights;
		for (size_t i = 0; i < DirectLights.size(); i++) {
			Lights.push_back(DirectLights[i]);
		}
		for (size_t i = 0; i < PointLights.size(); i++) {
			Lights.push_back(PointLights[i]);
		}
		for (size_t i = 0; i < SpotLights.size(); i++) {
			Lights.push_back(SpotLights[i]);
		}

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, LightListIndex);
		GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
		std::cout << sizeof(float) * Lights.size() << std::endl;

		memcpy(p, Lights.data(), sizeof(float) * Lights.size());
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	}

	void RemoveLight(LightType light, int index) {

		switch (light)
		{
		case Direct:


			break;
		case Point:


			break;
		case Spot:


			break;
		}
	}

public:
	const int DirectLightStride = 80;

private:
	std::vector<float> DirectLights;
	int DirectNum;
	std::vector<float> PointLights;
	std::vector<float> SpotLights;

	GLuint LightListIndex;
};
