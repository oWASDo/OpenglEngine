#include "Texture.h"
#include "Stb_image.h"
#include <iostream>

Texture::Texture(const std::string & path, const std::string& shaderTextureNam)
	:filePth(path), localBuffer(nullptr), width(0), height(0), BPP(0), shaderTextureName(shaderTextureNam)
{
	stbi_set_flip_vertically_on_load(true);

	//glEnable(GL_TEXTURE_2D);
	localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);


	if (localBuffer)
	{
		stbi_image_free(localBuffer);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

void Texture::Bind(GLuint slot, GLuint shader) {

	GLuint dsa = GL_TEXTURE0 + slot;
	glActiveTexture(dsa);
	//glTextureParameteri
	glBindTexture(GL_TEXTURE_2D, textureID);

	const char* name = shaderTextureName.c_str();
	GLint ShaderUniform = glGetUniformLocation(shader, name);
	if (ShaderUniform == -1) {
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << err;
		}
//		exit(-10);
	}
	glUniform1i(ShaderUniform, slot);



	//glBindTexture(GL_TEXTURE_2D, uniformLocation);
	while (GLenum error = glGetError())
	{
		std::cout << "error (" << error << ")" << std::endl;
	}
}

