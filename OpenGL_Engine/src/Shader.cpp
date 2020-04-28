#include "Shader.h"
#include "ShaderList.h"
Shader::Shader(std::string & vertexShader, std::string & fragmentShader) {
	generateShader(vertexShader, fragmentShader);
}

Shader::Shader(std::string & completeShader) {
	generateShader(completeShader);
}

Shader::Shader(const char * filePath) {
	generateShaderFromPath(filePath);
}

Shader::Shader(const char * vertexShader, const char * fragmentShader) {
	generateShaderFromPath(vertexShader, fragmentShader);
}

Shader::~Shader()
{
	blobs.fragmentBlob.clear();
	blobs.geometryBlob.clear();
	blobs.vertexBlob.clear();
	glDeleteProgram(mainShader);
}

GLuint Shader::CompileShader(unsigned int type, const std::string & source)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)(alloca(length * sizeof(char)));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "failed to compile shader" << std::endl;
		std::cout << message << std::endl;
		if (type == GL_VERTEX_SHADER) {
			std::cout << "vertex Shader Error" << std::endl;
			exit(-3);
		}
		else if (type == GL_FRAGMENT_SHADER) {
			std::cout << "fragment/pixel Shader Error" << std::endl;
			exit(-4);
		}
		glDeleteShader(id);
		return 0;
	}

	return id;
}

void Shader::generateShader(std::string & vertexShaderPath, std::string & fragmentShaderPath)
{
	blobs.vertexBlob = vertexShaderPath;
	blobs.fragmentBlob = fragmentShaderPath;
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShaderPath);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
	composeShader(vs, fs);
}

void Shader::generateShader(std::string & completeShader)
{
	dividShadersSource(completeShader);
	GLuint vs = CompileShader(GL_VERTEX_SHADER, blobs.vertexBlob);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, blobs.fragmentBlob);
	composeShader(vs, fs);
}

void Shader::generateShaderFromPath(const char * filePath)
{
	if (!ShaderList::Exist(filePath, mainShader))
	{
		reedAndDiveidShadersSource(filePath);
		GLuint vs = CompileShader(GL_VERTEX_SHADER, blobs.vertexBlob);
		GLuint fs = CompileShader(GL_FRAGMENT_SHADER, blobs.fragmentBlob);
		composeShader(vs, fs);
		ShaderList::Add(filePath, mainShader);
	}
}

void Shader::generateShaderFromPath(const char * vertexFilePath, const char * fragmentFilePath)
{
	blobs.vertexBlob = ReadFile(vertexFilePath);
	blobs.fragmentBlob = ReadFile(fragmentFilePath);
	GLuint vs = CompileShader(GL_VERTEX_SHADER, blobs.vertexBlob);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, blobs.fragmentBlob);
	composeShader(vs, fs);
}

void Shader::composeShader(GLuint vs, GLuint fs)
{
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	mainShader = program;
}

void Shader::reedAndDiveidShadersSource(std::string filePath)
{
	//readFile
	std::string file = ReadFile(filePath);
	dividShadersSource(file);
}

void Shader::dividShadersSource(std::string file)
{
	size_t pvs = file.find("#s vertex start") + sizeof("#s vertex start");
	size_t pve = file.find("#s vertex end");
	size_t pvsize = pve - pvs;
	size_t pvpos = pvs;

	//calculate fragment part
	size_t pfs = file.find("#s fragment start") + sizeof("#s fragment start");
	size_t pfe = file.find("#s fragment end");
	size_t pfsize = pfe - pfs;
	size_t pfpos = pfs;

	//find part
	std::string vertex = file.substr(pvpos, pvsize);
	std::string fragment = file.substr(pfpos, pfsize);
	//assign parts
	blobs.vertexBlob = vertex;
	blobs.fragmentBlob = fragment;
}

void Shader::Bind() {
	glUseProgram(mainShader);

}
