#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
using namespace glm;
using namespace std;

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class Entity {

	protected:
		GLuint VAO;
		GLuint VBO_V;
		GLuint VBO_C;
		vector<vec3> vertices;
		vector<vec4> colors;
		vector<vec3> cpCoordinates;	// Coordinate dei punti di controllo
		vector<vec4> cpColors;		// Colori dei punti di controllo
		int nCP;					// Numero massimo di punti di controllo (punti di interpolazione)
		mat4 model;					// Matrice di modellazione: traslazione * rotazione * scala
		float xShiftValue;			// Valore di traslazione per la x
		float yShiftValue;			// Valore di traslazione per la y
		float scaleValue;			// Valore di scalatura
		float rotationValue;		// Valore di rotazione

	public:
		void createPolygonalShape(vector<vec3> polygonVertices, vec3 center, vec4 color1, vec4 color2);
		void createHermiteShape(vector<vec3> controlPoints, vec3 center, vec4 color1, vec4 color2);
		void initVAO();
		void updateVAO();
		GLuint* getVAO();
		GLuint* getVerticesVBO();
		GLuint* getColorsVBO();
		vector<vec3> getVertices();
		vector<vec4> getVerticesColors();
		vector<vec3> getControlPointsCoordinates();
		vector<vec4> getControlPointsColors();
		int getNumberOfVertices();
		int getNumberOfControlPoints();
		mat4* getModel();
		float getXShiftValue();
		float getYShiftValue();
		float getScaleValue();
		float getRotationValue();

};

class Player : public Entity {

	private:
		Direction direction;
		bool alive;

	public:
		Player();
		Direction getDirection();
		void shoot();

};