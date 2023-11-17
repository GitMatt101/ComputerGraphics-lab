#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "lib.h"
#pragma warning(disable : 4996)

#define WIDTH 1280
#define HEIGHT 720

#define DEFAULT_SIZE 50.0f

static unsigned int programId;

mat4 Projection;
GLuint MatProj, MatModel;

Player player;

void INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();
	char* vertexShader = (char*)"vertexShader_M.glsl";
	char* fragmentShader = (char*)"fragmentShader_M.glsl";
	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);
}

void INIT_VAO(void)
{
	vec4 color1 = vec4(0.0f, 0.3f, 0.0f, 1.0f);
	vec4 color2 = vec4(0.7f, 0.2f, 0.2f, 1.0f);
	vector<vec3> polygonVertices = readPolygonVertices((char*)"tank.txt");
	vec3 center = vec3(0.0f, -0.15f, 0.0f);
	player.createPolygonalShape(polygonVertices, center, color1, color2);
	player.initVAO();

	Projection = ortho(0.0f, float(WIDTH), 0.0f, float(HEIGHT));
	MatProj = glGetUniformLocation(programId, "Projection");
	MatModel = glGetUniformLocation(programId, "Model");

	glViewport(0, 0, WIDTH, HEIGHT);
}

void update(int value)
{
	updateShapeVAO(&player);
	glutTimerFunc(50, update, 0);
	glutPostRedisplay();
}

void drawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	*player.getModel() = mat4(1.0);
	*player.getModel() = translate(*player.getModel(), vec3((float)WIDTH / 2, (float)HEIGHT / 2, 0.0f));
	*player.getModel() = scale(*player.getModel(), vec3(DEFAULT_SIZE * player.getScaleValue(), DEFAULT_SIZE * player.getScaleValue(), 1.0f));

	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(*player.getModel()));
	glBindVertexArray(*player.getVAO());
	glDrawArrays(GL_TRIANGLE_FAN, 0, player.getNumberOfVertices());
	glBindVertexArray(0);
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Tanks");
	glutDisplayFunc(drawScene);
	glewExperimental = GL_TRUE;
	glewInit();
	INIT_SHADER();
	INIT_VAO();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutTimerFunc(50, update, 0);
	glutMainLoop();
}