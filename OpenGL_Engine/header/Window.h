#pragma once
#include "GraphicHeader.h"
#include <iostream>

class Window
{
public:
	Window(GLuint width, GLuint heigth, const char* WindowTile, GLFWmonitor* monitor = nullptr, GLFWwindow* window = nullptr);
	Window(GLuint width, GLuint heigth, const std::string WindowTile, GLFWmonitor* monitor = nullptr, GLFWwindow* window = nullptr);

	~Window();
	GLFWwindow* GetWindow();
private:
	GLFWwindow* rawWindow;

};
