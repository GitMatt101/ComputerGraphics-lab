#include <iostream>
#include "ShaderMaker.h"
#include "lib.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
static unsigned int programId;

#define PI 3.14159265358979323846
const int width = 800;	// Larghezza della finestra
const int height = 600;	// Altezza della finestra

// Struct di una figura geometrica generica
typedef struct {
	GLuint VAO;				// VAO della figura
	GLuint VBO_P;			// VBO per le coordinate posizionali
	GLuint VBO_C;			// VBO per i colori
	int nTriangles;			// Numero di triangoli da disegnare
	vector<vec3> vertices;	// Vertici
	vector<vec4> colors;	// Colori
	mat4 model;				// Matrice di Modellazione: Traslazione*Rotazione*Scala
} Shape;

Shape butterfly;
mat4 Projection;			// Matrice per il cambio di sistema di riferimento
GLuint MatProj, MatModel;	// Matrici usate per le trasformazioni geometriche

float scaling = 1.0f;		// Coefficiente di scalatura
float rotationAngle = 0.0f;	// Angolo di rotazione

// Inizializza il VAO di una figura
void INIT_SHAPE_VAO(Shape* shape)
{
	glGenVertexArrays(1, &shape->VAO);
	glBindVertexArray(shape->VAO);

	glGenBuffers(1, &shape->VBO_P);
	glBindBuffer(GL_ARRAY_BUFFER, shape->VBO_P);
	glBufferData(GL_ARRAY_BUFFER, shape->vertices.size() * sizeof(vec3), shape->vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &shape->VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, shape->VBO_C);
	glBufferData(GL_ARRAY_BUFFER, shape->colors.size() * sizeof(vec4), shape->colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

// Riempie la struct con i vertici e i colori
void drawButterfly(float cx, float cy, float raggiox, float raggioy, Shape* butterfly)
{
	float stepA = (2 * PI) / butterfly->nTriangles;
	float theta, x, y;

	butterfly->vertices.push_back(vec3(cx, cy, 0.0));
	butterfly->colors.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));

	for (int i = 0; i <= butterfly->nTriangles; i++)
	{
		theta = (float)i * stepA;
		x = cx + raggiox * (sin(theta) * (exp(cos(theta)) - 2 * cos(4 * theta)) + pow(sin(theta / 12), 5));
		y = cy + raggioy * (cos(theta) * (exp(cos(theta)) - 2 * cos(4 * theta)) + pow(sin(theta / 12), 5));
		butterfly->vertices.push_back(vec3(x, y, 0.0f));
		butterfly->colors.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

void INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();
	char* vertexShader = (char*)"vertexShader.glsl";
	char* fragmentShader = (char*)"fragmentShader.glsl";
	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);
}

void INIT_VAO(void)
{
	butterfly.nTriangles = 300;

	drawButterfly(0.0f, 0.0f, 0.2f, 0.2f, &butterfly);
	INIT_SHAPE_VAO(&butterfly);

	// Il sistema del quadrato con dimensioni che vanno da -1 a 1 viene trasformato in un sistema che va da (0, 0) a (width, height)
	// La figura sarà comunque centrata in un sistema (-1, 1), a cui potranno essere applicate delle trasformazioni geometriche
	Projection = ortho(0.0f, float(width), 0.0f, float(height));
	MatProj = glGetUniformLocation(programId, "Projection");
	MatModel = glGetUniformLocation(programId, "Model");
}

void drawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	butterfly.model = mat4(1.0f);	// Matrice identità
	// Traslazione della figura al centro della finestra
	butterfly.model = translate(butterfly.model, vec3(width / 2, height / 2, 0.0f));
	// Scalatura delle dimensioni della figura (100 sono pixel)
	butterfly.model = scale(butterfly.model, vec3(100.0f * scaling, 100.0f * scaling, 1.0f));
	// Rotazione della figura attorno a un asse (in questo caso l'asse z)
	butterfly.model = rotate(butterfly.model, radians(rotationAngle), vec3(0.0f, 0.0f, 1.0f));

	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(butterfly.model));

	glBindVertexArray(butterfly.VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, butterfly.vertices.size());
	glBindVertexArray(0);
	glutSwapBuffers();
}

// Aggiorna il coefficiente per la scalatura della figura ogni 50 ms
void updateScale(int value) {
	scaling *= 1.1f;
	if (scaling > 4.0f)
		scaling = 1.0f;
	glutTimerFunc(50, updateScale, 0);
	glutPostRedisplay();
}

// Aggiorna l'angolo di rotazione ogni 5 ms
void updateAngle(int value) {
	rotationAngle += PI / 4;
	glutTimerFunc(5, updateAngle, 0);
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Trasformazioni OpenGL");
	glutDisplayFunc(drawScene);
	glewExperimental = GL_TRUE;
	glewInit();
	INIT_SHADER();
	INIT_VAO();
	glEnable(GL_BLEND);		//Per gestire i colori con trasparenza: mescola i colori di geometrie hce si sovrappongono
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	// Attiva due funzioni che si eseguono in loop per l'aggiornamento della scalatura e dell'angolo di rotazione
	// Argomenti: tempo tra un'esecuzione e quella successiva (in ms), funzione da ripetere, valore da passare
	// (noi il valore non lo usiamo ma è da mettere comunque)
	glutTimerFunc(50, updateScale, 0);
	glutTimerFunc(50, updateAngle, 0);

	glutMainLoop();
}