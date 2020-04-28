#pragma once

#include <fbxsdk.h>
#include <iostream>
#include <vector>
#include <memory>
#include "Buffer.h"
#include <algorithm>
#include <map>


struct VertexIndex
{
	int index;
	float value;
};
struct NodeAndType {
	fbxsdk::FbxNode* node;
	fbxsdk::FbxNodeAttribute::EType type;
};

class FBXpaser
{
public:
	static void Parser(const char* fileName, int child, std::vector<float>* vertPos, std::vector<float>* uvPos = nullptr, std::vector<float>* normalPos = nullptr, std::vector<unsigned int>* indexes = nullptr);

	static void Parser2(const char* fileName, int child, std::vector<float>* vertPos, std::vector<float>* uvPos = nullptr, std::vector<float>* normalPos = nullptr, std::vector<unsigned int>* indexes = nullptr) {



#pragma region MyRegion


		// Init meneager
		FbxManager* fbxMenager = FbxManager::Create();

		// Create an IOSettings object.
		FbxIOSettings * ios = FbxIOSettings::Create(fbxMenager, IOSROOT);
		fbxMenager->SetIOSettings(ios);

		// Create importer
		FbxImporter* importer = FbxImporter::Create(fbxMenager, "");

		// File name
		//const char * fileName = "Content/Mesh/FBX/AskeladFixedScale.fbx";

#pragma endregion

		bool inizializeStatus = importer->Initialize(fileName, -1, fbxMenager->GetIOSettings());

		if (!inizializeStatus) {
			std::cout << "Call to FbxImporter::Initialize() failed.\n";
			std::cout << "Error returned: " << importer->GetStatus().GetErrorString() << "\n\n" << std::endl;
			return;
		}
		else {
			FbxScene* scene = FbxScene::Create(fbxMenager, "");
			bool importStatus = importer->Import(scene);
			if (importStatus) {
				FbxGeometryConverter converter(fbxMenager);
				converter.Triangulate(scene, true);

				std::vector<fbxsdk::FbxNode*> nodes;
				fbxsdk::FbxNode* usedNode;
				usedNode = scene->GetRootNode();
				nodes.push_back(usedNode);

				GetAllCHild(usedNode, &nodes);



				size_t count = nodes.size();
				for (size_t i = 0; i < count; i++)
				{
					fbxsdk::FbxNode* forNode;

					forNode = nodes[i];

					fbxsdk::FbxNodeAttribute* nodeAttribute = forNode->GetNodeAttribute();

					if (nodeAttribute == nullptr)
					{
						//std::cout << "null" << std::endl;

					}
					else
					{
						fbxsdk::FbxNodeAttribute::EType lAttributeType;

						lAttributeType = nodeAttribute->GetAttributeType();

						if (fbxsdk::FbxNodeAttribute::eMesh == lAttributeType)
						{
							fbxsdk::FbxMesh* mesh = forNode->GetMesh();


							std::vector<int> inds;
							for (int i = 0; i < mesh->GetPolygonCount(); i++) {
								int index0 = mesh->GetPolygonVertex(i, 0);
								int index1 = mesh->GetPolygonVertex(i, 1);
								int index2 = mesh->GetPolygonVertex(i, 2);
								inds.push_back(index0);
								inds.push_back(index1);
								inds.push_back(index2);
								if (indexes != nullptr)
								{
									indexes->push_back(index0);
									indexes->push_back(index1);
									indexes->push_back(index2);
								}


								bool aIndex = false;
								bool bIndex = false;
								bool cIndex = false;
								if (indexes != nullptr) {
									if ((std::find(inds.begin(), inds.end(), index0) != inds.end()))
										aIndex = true;
									if ((std::find(inds.begin(), inds.end(), index1) != inds.end()))
										bIndex = true;
									if ((std::find(inds.begin(), inds.end(), index2) != inds.end()))
										cIndex = true;
								}

/*                  */#pragma region vecPos
								if (!aIndex) {
									FbxVector4 a;
									a = mesh->GetControlPointAt(index0);
									vertPos->push_back(a[0] * 0.1f);
									vertPos->push_back(a[1] * 0.1f);
									vertPos->push_back(a[2] * 0.1f);
								}
								if (!bIndex) {
									FbxVector4 b;
									b = mesh->GetControlPointAt(index1);
									vertPos->push_back(b[0] * 0.1f);
									vertPos->push_back(b[1] * 0.1f);
									vertPos->push_back(b[2] * 0.1f);
								}
								if (!cIndex) {
									FbxVector4 c;
									c = mesh->GetControlPointAt(index2);
									vertPos->push_back(c[0] * 0.1f);
									vertPos->push_back(c[1] * 0.1f);
									vertPos->push_back(c[2] * 0.1f);
								}



#pragma endregion

								if (normalPos != nullptr) {
									fbxsdk::FbxVector4 nor_a, nor_b, nor_c;

									mesh->GetPolygonVertexNormal(i, 0, nor_a);
									mesh->GetPolygonVertexNormal(i, 1, nor_b);
									mesh->GetPolygonVertexNormal(i, 2, nor_c);
									if (!aIndex) {
										normalPos->push_back(nor_a[0]);
										normalPos->push_back(nor_a[1]);
										normalPos->push_back(nor_a[2]);
									}
									if (!bIndex) {
										normalPos->push_back(nor_b[0]);
										normalPos->push_back(nor_b[1]);
										normalPos->push_back(nor_b[2]);
									}
									if (!cIndex) {
										normalPos->push_back(nor_c[0]);
										normalPos->push_back(nor_c[1]);
										normalPos->push_back(nor_c[2]);
									}

								}

								if (uvPos != nullptr) {
									fbxsdk::FbxVector2 uv_a, uv_b, uv_c;
									FbxStringList uvName;
									mesh->GetUVSetNames(uvName);
									bool l = true;

									mesh->GetPolygonVertexUV(i, 0, uvName[0], uv_a, l);
									mesh->GetPolygonVertexUV(i, 1, uvName[0], uv_b, l);
									mesh->GetPolygonVertexUV(i, 2, uvName[0], uv_c, l);

									if (!aIndex) {

										uvPos->push_back(uv_a[0]);
										uvPos->push_back(uv_a[1]);
									}
									if (!bIndex) {

										uvPos->push_back(uv_b[0]);
										uvPos->push_back(uv_b[1]);
									}
									if (!cIndex) {

										uvPos->push_back(uv_c[0]);
										uvPos->push_back(uv_c[1]);
									}
								}
							}
						}
					}


				}

			}




		}

		importer->Destroy();
		/*fbxsdk::FbxNode* node;
		node = scene->GetRootNode();
		node->GetNodeAttribute()->GetAttributeType();*/
	}

private:

	static unsigned int FindIndexFromNumber(std::vector<unsigned int>* vector, unsigned int toFind);

	static void GetAllCHild(fbxsdk::FbxNode* usedNode, std::vector<fbxsdk::FbxNode*>* nodes) {

		for (size_t i = 0; i < usedNode->GetChildCount(); i++)
		{
			fbxsdk::FbxNode * node = usedNode->GetChild(i);
			nodes->push_back(node);
			GetAllCHild(node, nodes);
		}
	}

};
