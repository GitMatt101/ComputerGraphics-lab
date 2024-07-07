#include "../lib.h"
#include "../header_files/init.h"
#include "../header_files/shaderMaker.h"
#include "../header_files/shape.h"
#include "../header_files/geometry.h"
#include "../header_files/view.h"
#include "../header_files/VAO_manager.h"

extern unsigned int programID;
extern unsigned int programID_text;

extern vector<Shape*> scene;
extern View camera;
extern Perspective cameraPerspective;

extern LightPoint light;
extern vector<Material> materials;

void initShader(void) {
	GLenum ErrorCheckValue = glGetError();
	char* vertexShader = (char*)"vertexShader_C.glsl";
	char* fragmentShader = (char*)"fragmentShader_C.glsl";
	programID = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programID);
	vertexShader = (char*)"VertexShader_Text.glsl";
	fragmentShader = (char*)"FragmentShader_Text.glsl";
	programID_text = ShaderMaker::createProgram(vertexShader, fragmentShader);

	light.position = { 0.0f, 3.0f, 0.0f };
	light.color = { 1.0f, 1.0f, 1.0f };
	light.power = 1.0f;

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
}

void initScene(void) {
	vector<vec3> normals;
	pair<vector<Vertex>, vector<GLuint>> c = createEllipsoid(1.0f, 1.0f, 1.0f, 30, &normals, vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Shape* ellipse = new Shape("Ellipse", c.first, c.second, normals, ShadingType::PHONG, MaterialType::EMERALD, 2.0f);
	initShapeVAO(ellipse);
	*ellipse->getModel() = scale(*ellipse->getModel(), vec3(2.5f, 2.5f, 2.5f));
	*ellipse->getNormals() = normals;
	scene.push_back(ellipse);
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