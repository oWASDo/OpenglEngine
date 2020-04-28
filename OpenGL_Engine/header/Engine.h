#pragma once
#include "Window.h"
#include "ShaderList.h"
#define PreInit if (!glfwInit()) return -1

class Engine
{
public:
	Engine(GLuint width, GLuint heigth, const char* WindowTile, GLFWmonitor* monitor = nullptr, GLFWwindow* win = nullptr);

	Engine(GLuint width, GLuint heigth, const std::string WindowTile, GLFWmonitor* monitor = nullptr, GLFWwindow* win = nullptr);


	~Engine();

private:
	int InitEngine();

public:
	void TerminateEngine();

	bool IsWindowClosed();

	void ClearScreen();

	void SecClanColor(float r, float g, float b, float a);

	void SetAndClear(float r, float g, float b, float a);

	void SwapBuffer();

	void PollEvent();



	Window* window;
};

