#include <iostream>
#include "ShaderMaker.h"
#include "lib.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

#define PI 3.14159265358979323846
#define WIDTH 1280
#define HEIGHT 720
#define MOVEMENT 10
#define SCALING 5

static unsigned int programId;

typedef struct {
	GLuint VAO;
	GLuint VBO_V;
	GLuint VBO_C;
	int nTriangles;
	vector<vec3> vertices;
	vector<vec4> colors;
	mat4 Model;
	float dx;		// Valore di traslazione sull'asse X
	float dy;		// Valore di traslazione sull'asse Y
	float scale;	// Valore di scalatura
	float angle;	// Angolo di rotazione
} Shape;

mat4 Projection;
GLuint MatProj, MatModel;

Shape butterfly = {};

void INIT_SHAPE_VAO(Shape* shape)
{
	glGenVertexArrays(1, &shape->VAO);
	glBindVertexArray(shape->VAO);
	glGenBuffers(1, &shape->VBO_V);
	glBindBuffer(GL_ARRAY_BUFFER, shape->VBO_V);
	glBufferData(GL_ARRAY_BUFFER, shape->vertices.size() * sizeof(vec3), shape->vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &shape->VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, shape->VBO_C);
	glBufferData(GL_ARRAY_BUFFER, shape->colors.size() * sizeof(vec4), shape->colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void drawButterfly(float cx, float cy, float raggiox, float raggioy, Shape* shape)
{
	shape->vertices.push_back(vec3(cx, cy, 0.0f));
	shape->colors.push_back(vec4(1.0f, 0.0f, 0.0f, 0.2f));
	float stepA = (2 * PI) / shape->nTriangles;
	float t,xx,yy;
	for (int i = 0; i <= shape->nTriangles; i++)
	{
		t = (float)i * stepA;
		xx = cx + raggiox * (sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5));
		yy = cy + raggioy * (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5));
		shape->vertices.push_back(vec3(xx,yy,0.0));
		shape->colors.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

void INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();
	char* vertexShader = (char*)"vertexShader_M.glsl";
	char* fragmentShader = (char*)"fragmentShader.glsl";
	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);
}

void INIT_VAO(void)
{
	butterfly.nTriangles = 180;
	butterfly.scale = 0.25f;
	butterfly.dx = 0.0f;
	butterfly.dy = 0.0f;
	butterfly.angle = 0.0f;
	drawButterfly(0.0f, 0.0f, butterfly.scale, butterfly.scale, &butterfly);
	INIT_SHAPE_VAO(&butterfly);
	Projection = ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT);
	MatProj = glGetUniformLocation(programId, "Projection");
	MatModel = glGetUniformLocation(programId, "Model");
	glViewport(0, 0, WIDTH, WIDTH);
}

// Funzione di call-back per la tastiera
/* Parametri:
	key -> tasto premuto
	(x, y) -> coordinate del cursore nel momento in cui viene premuto il tasto */
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'a':
			butterfly.dx -= MOVEMENT;
			break;
		case 'd':
			butterfly.dx += MOVEMENT;
			break;
		case 'w':
			butterfly.dy += MOVEMENT;
			break;
		case 's':
			butterfly.dy -= MOVEMENT;
			break;
		case 'q':
			butterfly.angle -= MOVEMENT;
			break;
		case 'e':
			butterfly.angle += MOVEMENT;
			break;
		case 27:		// Tasto ESC
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();	// la funzione drawScene() viene riattivata con i parametri aggiornati
}

// Funzione di call-back per il mouse. Quando viene clickato il tasto sinistro la farfalla si sposta in quel punto
/* Parametri:
	button -> tasto del mouse premuto (GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON)
	state -> indica se il tasto è stato premuto (GLUT_DOWN) o rilasciato (GLUT_UP)
	(x, y) -> coordinate del cursore nel momento in cui il tasto viene premuto */
void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		butterfly.dx = (float)x - (float)(WIDTH / 2);
		butterfly.dy = (float)(HEIGHT / 2) - (float)y;	// L'origine (0, 0) si trova nell'angolo in alto a sinistra
		glutPostRedisplay();	// la funzione drawScene() viene riattivata con i parametri aggiornati
	}
}

// Funzione di call-back per il mouse. Quando viene usata la rotellina la figura diventerà più grande/piccola
/* Parametri:
	wheel -> numero di rotelline, se il mouse ne ha solo una allora sarà 0
	direction -> direzione di scorrimento (+1 = avanti, -1 = indietro)
	(x, y) -> coordinate del cursore nel momento in cui la rotellina viene usata*/
void myMouseWheel(int wheel, int direction, int x, int y)
{
	if (direction == 1)
		butterfly.scale += (float)SCALING;
	else
		butterfly.scale -= (float)SCALING;
	glutPostRedisplay();
}

// Funzione di call-back per il movimento del cursore mentre un pulsante (del mouse) è premuto
/* Parametri:
	(x, y) -> coordinate del cursore*/
void mouseMotion(int x, int y)
{
	butterfly.dx = (float)x - (float)(WIDTH / 2);
	butterfly.dy = (float)(HEIGHT / 2) - (float)y;	// L'origine (0, 0) si trova nell'angolo in alto a sinistra
	glutPostRedisplay();	// la funzione drawScene() viene riattivata con i parametri aggiornati
}

// Funzione di call-back per il movimento del cursore
/* Parametri:
	(x, y) -> coordinate del cursore*/
void passiveMouseMotion(int x, int y)
{
	butterfly.dx = (float)x - (float)(WIDTH / 2);
	butterfly.dy = (float)(HEIGHT / 2) - (float)y;	// L'origine (0, 0) si trova nell'angolo in alto a sinistra
	glutPostRedisplay();	// la funzione drawScene() viene riattivata con i parametri aggiornati
}

void drawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	butterfly.Model = mat4(1.0);
	butterfly.Model = translate(butterfly.Model, vec3((float)(WIDTH / 2) + butterfly.dx, (float)(HEIGHT / 2) + butterfly.dy, 0.0f));
	butterfly.Model = scale(butterfly.Model, vec3(100.0f + butterfly.scale, 100.0f + butterfly.scale, 1.0f));
	butterfly.Model = rotate(butterfly.Model, radians(butterfly.angle), vec3(0.0f, 0.0f, 1.0f));

	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(butterfly.Model));
	glBindVertexArray(butterfly.VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, butterfly.vertices.size());
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
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Modellazione Scena 2D");
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(myKeyboard);		// Imposta la funzione myKeyboard per le interazioni con la tastiera
	glutMouseFunc(myMouse);				// Imposta la funzione myMouse per le interazioni con il mouse
	glutMouseWheelFunc(myMouseWheel);	// Imposta la funzione myMouseWheel per le interazioni con la rotellina del mouse
	glutMotionFunc(mouseMotion);		// Imposta la funzione mouseMotion per il movimento del cursore premendo un tasto del mouse
	//glutPassiveMotionFunc(passiveMouseMotion);	// Imposta la funzione passiveMouseMotion per il movimento del cursore senza premere tasti
	glewExperimental = GL_TRUE;
	glewInit();
	INIT_SHADER();
	INIT_VAO();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}