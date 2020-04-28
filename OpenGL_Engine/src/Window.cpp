#include "Window.h"

Window::Window(GLuint width, GLuint heigth, const std::string WindowTile, GLFWmonitor * monitor, GLFWwindow * window)
{
	rawWindow = glfwCreateWindow(width, heigth, WindowTile.c_str(), monitor, window);

}

Window::~Window()
{
}

GLFWwindow * Window::GetWindow()
{
	return rawWindow;

}

Window::Window(GLuint width, GLuint heigth, const char * WindowTile, GLFWmonitor * monitor, GLFWwindow * window)
{
	rawWindow = glfwCreateWindow(width, heigth, WindowTile, monitor, window);

}
