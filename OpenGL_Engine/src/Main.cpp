#include "GraphicHeader.h"
#include <iostream>
#include <string>
#include "FileReader.h"
#include "Shader.h"
#include "Engine.h"
#include <fbxsdk.h>
#include <fbxsdk/fileio/fbxiosettings.h>
#include "Material.h"
#include "Buffer.h"
#include "Utils.h"
#include "FBXParser.h"
#include "Uniform.h"
#include "LightSystem.h"
#include "Vector.h"

//while (GLenum error = glGetError())
//{
//	std::cout << "error (" << error << ")" << std::endl;
//}
int main(void) {



	vector<float> pos;
	vector<float> norm;
	vector<float> uv;
	vector<unsigned int> index;
	FBXpaser::Parser2("Content/Mesh/FBX/MotusMan_v2.fbx", 1, &pos, &uv, &norm);//, &index);

	Engine* engine;

	/* Create a windowed mode window and its OpenGL context */
	/* Make the window's context current */

	engine = new Engine(1080, 720, "Engine", nullptr, nullptr);


	Buffer buffers[3] = {
		Buffer(pos.data(), sizeof(float) * pos.size(), 3,0),
		Buffer(norm.data(), sizeof(float) * norm.size(), 3,1),
		Buffer(uv.data(), sizeof(float) * uv.size(), 2,2),
	};

	UniformElement uniArr[1]{
		{"Col",3,UnifromType::Float}
	};

	Texture texts[1]{
		Texture("Content/Image/MCG_diff.jpg", "TextureAlbedo"),
		//Texture("Content/Image/MCG_norm.jpg", "TextureNorm",2)

	};

	Material* material = new Material("Content/Shader/BasicShader.glsl", buffers, 3, texts, 1, uniArr, 0);//, index.data(), index.size());

	material->Use();


	LightSystem lights = LightSystem();
	lights.AddDirectLight(1, Vector(0.0f, 1.0f, 0.0f));
	lights.AddDirectLight(1, Vector(1.0f, 0.0f, -0.0f));
	//lights.AddDirectLight(1, Vector(0 ,0.0f, 1));
	lights.UpdateBuffer();


	//Texture texts2[1]{
	//	Texture("Content/Image/MCG_norm.jpg", "TextureAlbedo"),
	//};

	//Material* material2 = new Material("Content/Shader/BasicShader.glsl", buffers, 3, texts2, 1, uniArr, 1);//, index.data(), index.size());

	//material2->Use();

#pragma region Second Material



	//float pos2[18]{
	//	-0.5f,-0.5f,0, //0
	//	0.5f,-0.5f,0,  //1
	//	-0.5f,0.5f,0,  //2
	//	0.5f,0.5f,0,   //3
	//};
	//for (size_t i = 0; i < 18; i++)
	//{
	//	pos2[i] *= 5;
	//}
	//GLuint ind[6]{
	//	0, 1, 2,
	//		1, 3, 2
	//};
	//float norm2[18]{
	//	1.0f,0.0f,0,
	//	1.0f,0.0f,0,
	//	1.0f,0.0f,0,
	//	1.0f,0.0f,0,
	//	1.0f,0.0f,0,
	//	1.0f,0.0f,0
	//};
	//float uv2[8]{
	//	0.0f,0.0f, //0
	//	1.0f,0.0f,  //1
	//	0.0f,1.0f,  //2
	//	1.0f,1.0f
	//};

	//Buffer buffers2[3] = {
	//	//Buffer(positions, sizeof(positions) , 3,0)
	//	Buffer(pos2, sizeof(pos2), 3,0),
	//	Buffer(norm2, sizeof(norm2), 3,1),
	//	Buffer(uv2, sizeof(uv2), 2,2)/*,
	//	Buffer(uv.data(), sizeof(float) * uv.size(), 2,1),
	//	Buffer(norm.data(), sizeof(float) * norm.size(), 3,2)*/
	//};
	//UniformElement uniArr2[1]{
	//	{"Col",3,UnifromType::Float}
	//};

	//Material* material2 = new Material("Content/Shader/BasicShader.glsl", buffers2, 3, nullptr, 0, uniArr2, 1, ind, 6);//, index.data(), index.size());

	//material2->Use();
#pragma endregion


	/* Loop until the user closes the window */
	while (!engine->IsWindowClosed())
	{
		/* Render here */
		engine->ClearScreen();
		//lights.UpdateBuffer();

		//glDrawArrays(GL_TRIANGLES, 0, 9);
		//material->ChangeUniformFloatFromName("Col", 0, 1, 0);
		//material2->ChangeUniformFloatFromName("Col", 1, 1, 0);

		//material->UseAndDraw();
		/*or (size_t i = 0; i < 5; i++)
		{
			material->Use();
		}*/
		material->UseAndDraw();
		//material2->UseAndDraw();
		//material2->UseAndDraw();


		/* Swap front and back buffers */
		engine->SwapBuffer();

		/* Poll for and process events */
		engine->PollEvent();
	}
	//	glDeleteShader(shader);
	engine->TerminateEngine();
	return 0;
}