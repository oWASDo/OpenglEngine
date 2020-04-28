#include "FBXParser.h"

void FBXpaser::Parser(const char * fileName, int child, std::vector<float>* vertPos, std::vector<float>* uvPos, std::vector<float>* normalPos, std::vector<unsigned int>* indexes)
{


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
			fbxsdk::FbxMesh* mesh;
			
			if (child < 0)
			{
				mesh = scene->GetRootNode()->GetMesh();

			}
			else {

				mesh = scene->GetRootNode()->GetChild(0)->GetMesh();
			}
			if (mesh == nullptr) {
				return;
			}
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

	importer->Destroy();
}

unsigned int FBXpaser::FindIndexFromNumber(std::vector<unsigned int>* vector, unsigned int toFind)
{
	for (unsigned int i = 0; i < vector->size(); i++)
	{
		if (vector->at(i) == toFind) {

			return i;
		}
	}
	return 0;
}
