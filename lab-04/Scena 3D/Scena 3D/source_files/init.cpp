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

void initShader(void) {
	GLenum ErrorCheckValue = glGetError();
	char* vertexShader = (char*)"vertexShader_C.glsl";
	char* fragmentShader = (char*)"fragmentShader_C.glsl";
	programID = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programID);
	vertexShader = (char*)"VertexShader_Text.glsl";
	fragmentShader = (char*)"FragmentShader_Text.glsl";
	programID_text = ShaderMaker::createProgram(vertexShader, fragmentShader);
}

void initScene(void) {
	pair<vector<Vertex>, vector<GLuint>> c = createCuboid(1.0f, 1.0f, 1.0f, vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f));
	Shape* cube = new Shape("Cube", c.first, c.second, 2.0f);
	initShapeVAO(cube);
	*cube->getModel() = scale(*cube->getModel(), vec3(2.5f, 2.5f, 2.5f));
	scene.push_back(cube);

	c = createEllipsoid(1.0f, 0.5f, 1.0f, 30, vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f));
	Shape* ellipse = new Shape("Ellipse", c.first, c.second, 2.0f);
	initShapeVAO(ellipse);
	*ellipse->getModel() = translate(*ellipse->getModel(), vec3(4.0f, 0.0f, 0.0f));
	*ellipse->getModel() = scale(*ellipse->getModel(), vec3(2.5f, 2.5f, 2.5f));
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