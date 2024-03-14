#pragma once

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Globals.h"
#include <vector>

struct App;

namespace ModelLoader
{

	struct VertexBufferAttribute
	{
		u8 location;
		u8 componentCount;
		u8 offset;
	};

	struct VertexBufferLayout
	{
		std::vector<VertexBufferAttribute> attributes;
		u8 stride;
	};

	struct VertexShaderAttribute
	{
		u8 location;
		u8 componentCount;
	};

	struct VertexShaderLayout
	{
		std::vector<VertexShaderAttribute> attributes;
	};

	struct VAO
	{
		GLuint handle;
		GLuint programHandle;
	};

	void ProcessAssimpMesh(const aiScene* scene, aiMesh* mesh, Mesh* myMesh, u32 baseMeshMaterialIndex, std::vector<u32>& submeshMaterialIndices);

	void ProcessAssimpMaterial(App* app, aiMaterial* material, Material& myMaterial, String directory);

	void ProcessAssimpNode(const aiScene* scene, aiNode* node, Mesh* myMesh, u32 baseMeshMaterialIndex, std::vector<u32>& submeshMaterialIndices);

	u32 LoadModel(App* app, const char* filename);
};

