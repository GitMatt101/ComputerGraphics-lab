#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "lib.h"
#pragma warning(disable : 4996)

#define WIDTH 1280
#define HEIGHT 720
#define PI 3.14159265358979323846

static unsigned int programId;

float angolo = 0, scaling = 1;

mat4 Projection;
GLuint MatProj, MatModel;
int nv_P;
float Tens = 0.0f;
float Bias = 0.0f;
float Cont = 0.0f;

int pval = 140;
float* t;

Shape butterfly = {}, heart = {};
Shape shape = {}, polygonal = {}, derivative = {};

vector<Shape> scene;

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
	butterfly.nTriangles = 180;
	butterfly.scaleValue = 0.2f;
	create_butterfly(0.0f, 0.0f, butterfly.scaleValue, butterfly.scaleValue, &butterfly, vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
	INIT_SHAPE_VAO(&butterfly);
	scene.push_back(butterfly);

	heart.nTriangles = 180;
	heart.scaleValue = 0.1f;
	create_heart(0.0f, 0.0f, heart.scaleValue, heart.scaleValue, &heart, vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f));
	INIT_SHAPE_VAO(&heart);
	scene.push_back(heart);

	vec4 color_top = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	vec4 color_bot = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	create_shape_from_file((char*)"myCurve.txt", &shape, &derivative);
	build_hermite_curve(color_top, color_bot, &shape, NULL, &derivative, &polygonal, false, pval, vec3(0.0f, 0.0f, 0.0f));

	// Costruire curva interpolante di Hermite e tassellarla con triangoli opportunamente
	INIT_SHAPE_VAO(&shape);

	// Projection è la matrice che mappa la finestra sul mondo nelle coordinate NDC (cormalizzate di device che trariano tra (-1, -1) ed (1, 1)
	Projection = ortho(0.0f, float(WIDTH), 0.0f, float(HEIGHT));

	// Viene ricavata la location della variabile Uniform Projection presente nel fragment shader
	MatProj = glGetUniformLocation(programId, "Projection");
	// Viene ricavata la location della variabile Uniform Model presente nel fragment shader
	MatModel = glGetUniformLocation(programId, "Model");

	glViewport(0, 0, WIDTH, HEIGHT); // Mappa le coordinate normlaizzate di device nella finestra sullo schermo
}

void update(int value)
{
	for (int i = 0; i < scene.size(); i++)
		UPDATE_SHAPE_VAO(&scene[i]);
	UPDATE_SHAPE_VAO(&shape);
	glutTimerFunc(50, update, 0);
	glutPostRedisplay();
}

void drawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int k = 0; k < scene.size(); k++)
	{
		scene[k].model = mat4(1.0);
		if (k == 0)
		{
			scene[k].model = translate(scene[k].model, vec3((float)WIDTH / 3, (float)HEIGHT / 2, 0.0f));
			scene[k].model = scale(scene[k].model, vec3(50.0f, 50.0f, 1.0f));
		}
		if (k == 1)
		{
			scene[k].model = translate(scene[k].model, vec3((float)WIDTH * 2 / 3, (float)HEIGHT / 2, 0.0f));
			scene[k].model = scale(scene[k].model, vec3(50.0, 50.0, 1.0f));
		}
		glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));	  // comunica i valori della variabile uniform Projection al vertex shader
		glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(scene[k].model)); // comunica i valori della variabile uniform Model al vertex shader
		glBindVertexArray(scene[k].VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, scene[k].nVertices);
		glBindVertexArray(0);
	}

	// Disegna la curva interpolante di Hermite dalle coordinate dei vertici di controllo salvate nel file mycurve.txt
	shape.model = mat4(1.0);
	shape.model = translate(shape.model, vec3((float)WIDTH / 2, (float)HEIGHT / 2, 0.0));
	shape.model = scale(shape.model, vec3(200.0f, 200.0f, 1.0f));

	// Posizionare, orientare e scalare la curva nel mondo
	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(shape.model));
	glBindVertexArray(shape.VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, shape.nVertices);
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
	glutCreateWindow("Modellazione Scena 2D");
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