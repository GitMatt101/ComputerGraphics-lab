#include <iostream>
#include "lib.h"
#include "header_files/shape.h"
#include "header_files/view.h"
#include "header_files/interactions.h"
#include "header_files/text.h"
#include "header_files/init.h"
#include "header_files/VAO_manager.h"
#pragma warning(disable : 4996)
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

vector<Shape*> scene;
View camera;
Perspective cameraPerspective;

mat4 projectionMatrix;
mat4 projectionMatrix_text;
mat4 view;

unsigned int programID;
unsigned int programID_text;
unsigned int uniformProjectionMatrix;
unsigned int uniformViewMatrix;
unsigned int uniformModelMatrix;
unsigned int textVAO;
unsigned int textVBO;

string transformation = "Translation";
string workingAxis = "X";

void drawScene(void) {
	projectionMatrix_text = ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT);
	projectionMatrix = perspective(radians(cameraPerspective.fov), cameraPerspective.aspect, cameraPerspective.nearPlane, cameraPerspective.farPlane);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(uniformProjectionMatrix, 1, GL_FALSE, value_ptr(projectionMatrix));

	// Creates the view matrix applied to the vertices (world coordinates), transforming them in camera coordinates.
	view = lookAt(vec3(camera.position), vec3(camera.target), vec3(camera.upVector));

	glUniformMatrix4fv(uniformViewMatrix, 1, GL_FALSE, value_ptr(view));
	glPointSize(10.0f);
	for (Shape* shape : scene) {
		*shape->getAnchorWorld() = *shape->getAnchorObj();
		*shape->getAnchorWorld() = *shape->getModel() * *shape->getAnchorWorld();
		
		glUniformMatrix4fv(uniformModelMatrix, 1, GL_FALSE, value_ptr(*shape->getModel()));
		glBindVertexArray(*shape->getVAO());

		int ind = shape->getIndexes()->size() - 1;

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, BUFFER_OFFSET(ind * sizeof(GLuint)));

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, shape->getIndexes()->size() * sizeof(GLuint), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	renderText(programID_text, projectionMatrix_text, transformation, textVAO, textVBO, 10.0f, (float)HEIGHT - 30.0f, 0.5f, vec3(1.0f, 0.0f, 1.0f));
	renderText(programID_text, projectionMatrix_text, workingAxis, textVAO, textVBO, 10.0f, (float)HEIGHT - 60.0f, 0.5f, vec3(1.0f, 0.0f, 1.0f));

	for (Shape* shape : scene) {
		if (shape->isSelected()) {
			renderText(programID_text, projectionMatrix_text, "Selected Object:", textVAO, textVBO, 10.0f, (float)HEIGHT - 90.0f, 0.5f, vec3(1.0f, 0.0f, 0.2f));
			renderText(programID_text, projectionMatrix_text, shape->getName(), textVAO, textVBO, 190.0f, (float)HEIGHT - 90.0f, 0.5f, vec3(1.0f, 0.0f, 0.2f));
		}
	}
	glutSwapBuffers();
	glUseProgram(programID);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3D Scene");
	glutDisplayFunc(drawScene);
	glutMouseFunc(select);
	glutKeyboardFunc(keyboardEvent);
	glutMouseWheelFunc(zoom);
	glewExperimental = GL_TRUE;
	glewInit();
	initShader();
	initScene();
	initCamera();
	initTextVAO(&textVAO, &textVBO);
	initFreetype();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	uniformProjectionMatrix = glGetUniformLocation(programID, "Projection");
	uniformModelMatrix = glGetUniformLocation(programID, "Model");
	uniformViewMatrix = glGetUniformLocation(programID, "View");

	glutMainLoop();
}