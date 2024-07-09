#include "../lib.h"
#include "../header_files/init.h"
#include "../header_files/shaderMaker.h"
#include "../header_files/mesh.hpp"
#include "../header_files/geometry.h"
#include "../header_files/view.h"
#include "../header_files/VAO_manager.h"
#include "../header_files/assimp.hpp"
#include "../header_files/texture.hpp"

extern unsigned int programId;
extern unsigned int programId_text;
extern unsigned int programId_cubemap;

extern unsigned int cubeMapTexture;

extern pair<vector<Mesh*>, vector<vector<Mesh*>>> scene;
extern Mesh* cubeMap;
extern View camera;
extern Perspective cameraPerspective;

extern LightPoint light;
extern vector<Material> materials;
extern vector<Shader> shaders;

void initShader(void) {
	GLenum ErrorCheckValue = glGetError();
	char* vertexShader = (char*)"vertexShader.glsl";
	char* fragmentShader = (char*)"fragmentShader.glsl";
	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);

	vertexShader = (char*)"VertexShader_Text.glsl";
	fragmentShader = (char*)"FragmentShader_Text.glsl";
	programId_text = ShaderMaker::createProgram(vertexShader, fragmentShader);

	vertexShader = (char*)"vertexShader_CubeMap.glsl";
	fragmentShader = (char*)"fragmentShader_CubeMap.glsl";
	programId_cubemap = ShaderMaker::createProgram(vertexShader, fragmentShader);
}

void initScene(void) {
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<vec3> normals;
	vector<vec2> textureCoordinates;
	createEllipsoid(1.0f, 1.0f, 1.0f, 30, vec4(1.0f, 0.0f, 0.0f, 1.0f), &vertices, &indices, &normals, &textureCoordinates);

	Mesh* sphere = new Mesh();
	sphere->setVertices(vertices);
	sphere->setIndices(indices);
	sphere->setNormals(normals);
	sphere->setTextureCoordinates(textureCoordinates);
	sphere->setModel(scale(*sphere->getModel(), vec3(2.5f, 2.5f, 2.5f)));
	sphere->setName("Sfera");
	sphere->setSphereRadius(2.5f);
	sphere->setTexture(loadTexture(((string)TEXTURE_PATH + "muromattoni.jpg").c_str(), false));
	sphere->toggleUseTexture();
	scene.first.push_back(sphere);

	//vector<Mesh*> mesh;
	//loadAssImp((MESH_PATH + (string)"Skull.obj").c_str(), &mesh);
	//for (Mesh* subMesh : mesh) {
	//	subMesh->setModel(scale(*subMesh->getModel(), vec3(5.0f, 5.0f, 5.0f)));
	//	subMesh->setModel(translate(*subMesh->getModel(), vec3(3.0f, 0.0f, 2.0f)));
	//	//subMesh->setModel(rotate(*subMesh->getModel(), radians(180.0f), vec3(0.0f, 1.0f, 0.0f)));
	//	subMesh->setMaterialType(MaterialType::SLATE);
	//}
	//scene.second.push_back(mesh);

	for (Mesh* mesh : scene.first)
		initMeshVAO(mesh);

	for (vector<Mesh*> mesh : scene.second) {
		for (Mesh* subMesh : mesh) {
			initMeshVAO(subMesh);
		}
	}
}

void initCamera(void) {
	camera.position = vec4(0.0f, 0.5f, 20.0f, 1.0f);
	camera.target = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	camera.direction = camera.target - camera.position;
	camera.upVector = vec4(0.0f, 1.0f, 0.0f, 0.0f);
	cameraPerspective.aspect = (GLfloat)WIDTH / (GLfloat)HEIGHT;
	cameraPerspective.fov = 45.0f;
	cameraPerspective.farPlane = 2000.0f;
	cameraPerspective.nearPlane = 0.1f;
}

void initMaterials(void) {
	materials.resize(6);
	materials[MaterialType::RED_PLASTIC].name = "Red Plastic";
	materials[MaterialType::RED_PLASTIC].ambient = red_plastic_ambient;
	materials[MaterialType::RED_PLASTIC].diffuse = red_plastic_diffuse;
	materials[MaterialType::RED_PLASTIC].specular = red_plastic_specular;
	materials[MaterialType::RED_PLASTIC].shininess = red_plastic_shininess;

	materials[MaterialType::EMERALD].name = "Emerald";
	materials[MaterialType::EMERALD].ambient = emerald_ambient;
	materials[MaterialType::EMERALD].diffuse = emerald_diffuse;
	materials[MaterialType::EMERALD].specular = emerald_specular;
	materials[MaterialType::EMERALD].shininess = emerald_shininess;

	materials[MaterialType::BRASS].name = "Brass";
	materials[MaterialType::BRASS].ambient = brass_ambient;
	materials[MaterialType::BRASS].diffuse = brass_diffuse;
	materials[MaterialType::BRASS].specular = brass_specular;
	materials[MaterialType::BRASS].shininess = brass_shininess;

	materials[MaterialType::SLATE].name = "Slate";
	materials[MaterialType::SLATE].ambient = slate_ambient;
	materials[MaterialType::SLATE].diffuse = slate_diffuse;
	materials[MaterialType::SLATE].specular = slate_specular;
	materials[MaterialType::SLATE].shininess = slate_shininess;

	materials[MaterialType::YELLOW].name = "Yellow";
	materials[MaterialType::YELLOW].ambient = yellow_ambient;
	materials[MaterialType::YELLOW].diffuse = yellow_diffuse;
	materials[MaterialType::YELLOW].specular = yellow_specular;
	materials[MaterialType::YELLOW].shininess = yellow_shininess;

	materials[MaterialType::NO_MATERIAL].name = "NO_MATERIAL";
	materials[MaterialType::NO_MATERIAL].ambient = vec3(1.0f, 1.0f, 1.0f);
	materials[MaterialType::NO_MATERIAL].diffuse = vec3(0.0f, 0.0f, 0.0f);
	materials[MaterialType::NO_MATERIAL].specular = vec3(0.0f, 0.0f, 0.0f);
	materials[MaterialType::NO_MATERIAL].shininess = 1.0f;

	light.position = { 0.0f, 3.0f, 0.0f };
	light.color = { 1.0f, 1.0f, 1.0f };
	light.power = 1.0f;
}

void initShaders(void) {
	shaders.resize(5);
	shaders[ShaderOption::NONE].value = 0;
	shaders[ShaderOption::NONE].name = "NONE";
	shaders[ShaderOption::GOURAD_SHADING].value = 1;
	shaders[ShaderOption::GOURAD_SHADING].name = "GOURAD SHADING";
	shaders[ShaderOption::PHONG_SHADING].value = 2;
	shaders[ShaderOption::PHONG_SHADING].name = "PHONG SHADING";
	shaders[ShaderOption::NO_TEXTURE].value = 3;
	shaders[ShaderOption::NO_TEXTURE].name = "NO TEXTURE";
	shaders[ShaderOption::WAVE].value = 4;
	shaders[ShaderOption::WAVE].name = "WAVE";
}

void initCubeMap(void) {
	cubeMap = new Mesh();
	vector<Vertex> vertices;
	vector<GLuint> indices;
	createCuboid(2.0f, 2.0f, 2.0f, vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f), &vertices, &indices);
	cubeMap->setVertices(vertices);
	cubeMap->setIndices(indices);
	initMeshVAO(cubeMap);

	vector<string> faces {
		(string)SKYBOX_PATH + "right.jpg",
		(string)SKYBOX_PATH + "left.jpg",
		(string)SKYBOX_PATH + "top.jpg",
		(string)SKYBOX_PATH + "bottom.jpg",
		(string)SKYBOX_PATH + "front.jpg",
		(string)SKYBOX_PATH + "back.jpg"
	};
	cubeMapTexture = loadCubeMap(faces);
}