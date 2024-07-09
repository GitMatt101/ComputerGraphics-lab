#include "../header_files/assimp.hpp"

void loadAssImp(const char* path, vector<Mesh*>* mesh) {
	Assimp::Importer importer;

	const aiScene* aiScene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!aiScene) exit(-1);

	const aiMesh* aiMesh;

	for (unsigned int i = 0; i < aiScene->mNumMeshes; i++)
	{
		Mesh* subMesh = new Mesh();
		aiMesh = aiScene->mMeshes[i];
		aiMaterial* aiMaterial = aiScene->mMaterials[aiMesh->mMaterialIndex];

		aiColor3D color;
		float value;

		Material material = subMesh->getMaterial();

		if (aiReturn_SUCCESS == aiMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color))
			material.ambient = vec3(color.r, color.g, color.b);

		if (aiReturn_SUCCESS == aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color))
			material.diffuse = vec3(color.r, color.g, color.b);
		else
			material.diffuse = vec3(1.0f, 0.2f, 0.1f);

		if (aiReturn_SUCCESS == aiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color))
			material.specular = vec3(color.r, color.g, color.b);
		else
			material.specular = vec3(0.5f, 0.5f, 0.5f);

		if (aiReturn_SUCCESS == aiMaterial->Get(AI_MATKEY_SHININESS_STRENGTH, value))
			material.shininess = value;
		else
			material.shininess = 50.0f;

		subMesh->setMaterial(material);

		for (unsigned int i = 0; i < aiMesh->mNumVertices; i++) {
			aiVector3D pos = aiMesh->mVertices[i];
			subMesh->getVertices()->push_back({
				vec3(pos.x, pos.y, pos.z),
				vec4(1.0, 0.0, 0.0, 1.0)
			});
			subMesh->getTextureCoordinates()->push_back(vec2(0.0f, 0.0f));
			aiVector3D n = aiMesh->mNormals[i];
			subMesh->getNormals()->push_back(vec3(n.x, n.y, n.z));
		}

		for (unsigned int i = 0; i < aiMesh->mNumFaces; i++) {
			subMesh->getIndices()->push_back(aiMesh->mFaces[i].mIndices[0]);
			subMesh->getIndices()->push_back(aiMesh->mFaces[i].mIndices[1]);
			subMesh->getIndices()->push_back(aiMesh->mFaces[i].mIndices[2]);
		}

		mesh->push_back(subMesh);
	}
}