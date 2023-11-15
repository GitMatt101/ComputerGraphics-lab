#include <iostream>
#include <fstream>
#include "lib.h"

#define WIDTH 1280
#define HEIGHT 720
#define PI 3.14159265358979323846

static unsigned int programId;

int selected_obj = -1;

bool mod_par_der = false;	//(0) 1 : (non) si intende agire sui parametri T,B,C nel calcolo numerico della derivative nel vertice di controllo selezionato; 
bool visualizzaTg = false;	//(0) 1 : (non) si intende visualizzare graficamente la tangente nei vertici di controllo

// Parametri per la modifica delle derivate agli estremi
float tens = 0.0f, bias = 0.0f, cont = 0.0f;  //Questa inizializzazione rappresenta le derivate come semplice rapporto incrementale

int metodo = 1;		// 1 --> interpolazione curve di Hermite | 2 --> approssimazione di forma curve di Bezier
int M_I = 0;
unsigned int lsceltavs, lsceltafs, loc_time, loc_res, loc_mouse;
mat4 Projection;
GLuint MatProj, MatModel;
vec2 res, mouse;

Shape curve = {}, polygonal = {}, derivative = {}, tangents = {}, axes = {};

int pval = 140;
float* t;

void mouseMotion(int x, int y)
{
	float c = -1.0;
	float d = 1.0;
	float mousex = (float)x;
	float mousey = (float)HEIGHT - y;

	mousex = c + mousex * (d - c) / (float)WIDTH;
	mousey = c + mousey * (d - c) / (float)HEIGHT;

	if (M_I == 1)
	{
		if (selected_obj >= 0)
		{
			curve.cpCoordinates[selected_obj] = vec3(mousex, mousey, 0.0f);
			curve.cpColors[selected_obj] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
		}
	}
	glutPostRedisplay();
}

void onMouse(int button, int state, int x, int y)
{
	float dist, dist1;
	float TOLL = 0.1f; // Tolleranza per la selezione del vertice di controllo da modificare
	float c = -1.0f;
	float d = 1.0f;

	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		float mousex = c + (float)x * (d - c) / (float)WIDTH;
		float mousey = c + ((float)HEIGHT - y) * (d - c) / (float)HEIGHT;

		if (M_I == 1 || mod_par_der)
		{
			selected_obj = 0;
			dist = sqrt((mousex - curve.cpCoordinates[0].x) * (mousex - curve.cpCoordinates[0].x) + (mousey - curve.cpCoordinates[0].y) * (mousey - curve.cpCoordinates[0].y));
			// Calcolo la distanza tra il punto in cui si trova attualmente il mouse e tutti i vertici di controllo sulla finestre
			// ed individuo l'indice selected_obj del vertice di controllo più vicino alla posizione del mouse
			for (int i = 1; i < curve.cpCoordinates.size(); i++)
			{
				dist1 = sqrt((mousex - curve.cpCoordinates[i].x) * (mousex - curve.cpCoordinates[i].x) + (mousey - curve.cpCoordinates[i].y) * (mousey - curve.cpCoordinates[i].y));

				if (dist1 < dist)
				{
					selected_obj = i;
					dist = dist1;
				}
			}

			if (dist > TOLL)
				selected_obj = -1;
			tens = 0.0f;
			cont = 0.0f;
			bias = 0.0f;
		}
		else if (M_I == 0)
		{
			curve.cpCoordinates.push_back(vec3(mousex, mousey, 0.0f));
			curve.cpColors.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));
			// Ad ogni vertice di controllo associo un valore vec3(0.0,0.0,0.0) per indicare che la derivative in quel vertice di controllo non è stata modificata
			derivative.cpCoordinates.push_back(vec3(0.0f, 0.0f, 0.0f));
		}
		else if (M_I == 2)
		{
			// Elimino l'ultimo vertice di controllo introdotto.
			curve.cpCoordinates.pop_back();
			curve.cpColors.pop_back();
		}
	}

	glutPostRedisplay();
}

void mykeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'T':
			tens += 0.1f;
			break;
		case 't':
			tens -= 0.1f;
			break;
		case 'C':
			cont += 0.1f;
			break;
		case 'c':
			cont -= 0.1f;
			break;
		case 'B':
			bias += 0.1f;
			break;
		case 'b':
			bias -= 0.1f;
			break;
	}
	// Modifico la derivative del vertice selezionato con valori tens, cont e bias selezionati da tastiera
	derivative.cpCoordinates.at(selected_obj).x = dx(selected_obj, t, tens, bias, cont, &polygonal);
	derivative.cpCoordinates.at(selected_obj).y = dy(selected_obj, t, tens, bias, cont, &polygonal);
	glutPostRedisplay();
}

void INIT_VAO(void)
{
	curve.nVertices = 140;
	INIT_SHAPE_VAO(&curve);

	polygonal.nCP = 20;
	INIT_CP_VAO(&polygonal);

	tangents.nCP = 20;
	INIT_CP_VAO(&tangents);

	axes.nCP = 4;
	axes.cpCoordinates.push_back(vec3(0.0f, 1.0f, 0.0f));
	axes.cpCoordinates.push_back(vec3(0.0f, -1.0f, 0.0f));
	axes.cpCoordinates.push_back(vec3(-1.0f, 0.0f, 0.0f));
	axes.cpCoordinates.push_back(vec3(1.0f, 0.0f, 0.0f));

	axes.cpColors.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	axes.cpColors.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	axes.cpColors.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	axes.cpColors.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));

	INIT_CP_VAO(&axes);
	UPDATE_CP_VAO(&axes);

	//Projection = ortho(0.0f, float(width), 0.0f, float(height));
	Projection = ortho(-1.0f, 1.0f, -1.0f, 1.0f);

	MatProj = glGetUniformLocation(programId, "Projection");
	MatModel = glGetUniformLocation(programId, "Model");
	glViewport(0.0f, 0.0f, WIDTH, HEIGHT);
}

void INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();
	char* vertexShader = (char*)"vertexShader_M.glsl";
	char* fragmentShader = (char*)"fragmentShader_M.glsl";
	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);
}

void drawScene(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	vec4 col_bottom = vec4{0.0f, 0.0f, 0.0f, 1.0f};
	vec4 col_top = vec4{0.0f, 0.0f, 0.0f, 1.0f};

	// Caso metodo=1 : costrusci curve di Hermite
	if (metodo == 1)
	{
		build_hermite_curve(col_top, col_bottom, &curve, &tangents, &derivative, &polygonal, visualizzaTg, pval, vec3(NULL, NULL, NULL));
		UPDATE_SHAPE_VAO(&curve);
		UPDATE_CP_VAO(&polygonal);
	}

	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
	// la matrice di Modellazione della curve coincide con la matrice identità, perché selezioniamo i punti con il mouse in coordinate del mondo
	curve.model = mat4(1.0);
	glPointSize(6.0);
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(curve.model));
	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
	axes.model = mat4(1.0);
	glPointSize(3.0);
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(axes.model));
	glBindVertexArray(axes.VAO);
	glDrawArrays(GL_LINES, 0, axes.cpCoordinates.size());
	glBindVertexArray(0);
	curve.model = mat4(1.0);

	// Dimensione in pixel di un punto dello schermo
	glPointSize(3.0);
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(curve.model));
	// Disegno la curve se ho pi� di 2 vertici di controllo
	if (polygonal.cpCoordinates.size() > 1)
	{
		glBindVertexArray(curve.VAO);
		glDrawArrays(GL_LINE_STRIP, 0, curve.vertices.size());
		glBindVertexArray(0);
	}

	// Disegno i vertici di controllo
	glBindVertexArray(polygonal.VAO);
	glDrawArrays(GL_POINTS, 0, polygonal.cpCoordinates.size());
	glBindVertexArray(0);

	// Se ho selezionato la costruzione della curve interpolante di Hermite, visualizzo le tangents se visualizzaTg=1
	if (metodo == 1)
	{
		if (visualizzaTg)
		{
			UPDATE_CP_VAO(&tangents);
			glBindVertexArray(tangents.VAO);
			glDrawArrays(GL_LINES, 0, tangents.cpCoordinates.size());
			glBindVertexArray(0);
		}
	}
	glutSwapBuffers();
}

void saveCurve(void)
{
	std::ofstream outputFile("mycurve.txt");
	if (outputFile.is_open())
	{
		for (int i = 0; i < curve.cpCoordinates.size(); i++)
			outputFile << curve.cpCoordinates[i].x << "  " << curve.cpCoordinates[i].y << "  " << curve.cpCoordinates[i].z << std::endl;
		outputFile.close();
	}
}

void interpolation(int num)
{
	metodo = 1;
	switch (num)
	{
		case 1:
			saveCurve();
			break;
		case 2:
			mod_par_der = true;
			M_I = -1;
			break;
		case 3:
			mod_par_der = false;
			break;
		case 4:
			visualizzaTg = true;
			break;
		case 5:
			visualizzaTg = false;
			break;
		case 6:
			curve.cpCoordinates.clear();
			break;
	}
	glutPostRedisplay();
}

void options(int num)
{
	M_I = num;
	if (M_I == 1)
		selected_obj = -1;
	glutPostRedisplay();
}

void menu(int num)
{
	glutPostRedisplay();
}

void createMenu(void)
{
	// Creazione sottomenu per l'inserimento di punti
	int optionsSubmenu = glutCreateMenu(options);
	glutAddMenuEntry("Inserisci", 0);
	glutAddMenuEntry("Sposta", 1);
	glutAddMenuEntry("Elimina", 2);

	// Creazione sottomenu per le curve di Hermite
	int interpolationSubMenu = glutCreateMenu(interpolation);
	glutAddMenuEntry("Calcola curve Interpolante", 0);
	glutAddMenuEntry("Salva control Points", 1);
	glutAddMenuEntry("Attiva Modalita' modifica tangents", 2);
	glutAddMenuEntry("Disattiva Modalita' modifica tangents", 3);
	glutAddMenuEntry("Attiva Visualizzazione tangents ", 4);
	glutAddMenuEntry("Disattiva Visualizzazione tangents ", 5);
	glutAddMenuEntry("Inserisci Nuova curve", 6);

	// Creazione del menu prinicpale
	int mainMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Editor Curve", -1);
	glutAddSubMenu("Modalita inserimento", optionsSubmenu);
	glutAddSubMenu("Curve cubiche di Hermite Interpolanti C1", interpolationSubMenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);	// Il menu verrà aperto premendo il tasto destro del mouse
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Editor Curve");
	glutDisplayFunc(drawScene);
	glutMouseFunc(onMouse);
	glutKeyboardFunc(mykeyboard);
	glewExperimental = GL_TRUE;
	glewInit();
	INIT_SHADER();
	INIT_VAO();
	createMenu();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMotionFunc(mouseMotion);
	glutMainLoop();
}