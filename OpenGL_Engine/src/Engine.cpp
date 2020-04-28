#include "Engine.h"

int Engine::InitEngine()
{
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window->GetWindow());
	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	return 0;
}
void Engine::TerminateEngine()
{
	glfwTerminate();
}

bool Engine::IsWindowClosed()
{
	return glfwWindowShouldClose(window->GetWindow());

}

void Engine::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	

}

void Engine::SecClanColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);

}

void Engine::SetAndClear(float r, float g, float b, float a)
{
	SecClanColor(r, g, b, a);
	ClearScreen();
}

void Engine::SwapBuffer()
{
	glfwSwapBuffers(window->GetWindow());

}

void Engine::PollEvent()
{
	glfwPollEvents();

}


Engine::Engine(GLuint width, GLuint heigth, const char * WindowTile, GLFWmonitor * monitor, GLFWwindow * win)
{
	if (!glfwInit())
		exit(-1);
	window = new Window(width, heigth, WindowTile, monitor, win);
	if (InitEngine() < 0)
	{
		exit(-1);
	}
}

Engine::Engine(GLuint width, GLuint heigth, const std::string WindowTile, GLFWmonitor * monitor, GLFWwindow * win)
{
	window = new Window(width, heigth, WindowTile, monitor, win);
	if (InitEngine() < 0)
	{
		exit(-1);
	}
}

Engine::~Engine()
{
	TerminateEngine();

}