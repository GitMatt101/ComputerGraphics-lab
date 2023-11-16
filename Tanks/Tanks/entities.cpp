#include "entities.h"
#include "VAO_manager.h"

void Entity::createPolygonalShape(vector<vec3> polygonVertices, vec3 center, vec4 color1, vec4 color2)
{
	vertices.push_back(center);
	colors.push_back(color2);
	for (int i = 0; i < polygonVertices.size(); i++) {
		vertices.push_back(vec3(polygonVertices[i].x, polygonVertices[i].y, 0.0f));
		colors.push_back(color1);
	}
}

void Entity::createHermiteShape(vector<vec3> controlPoints, vec3 center, vec4 color1, vec4 color2)
{

}

void Entity::initVAO()
{
	initShapeVAO(this);
}

void Entity::updateVAO()
{
	updateShapeVAO(this);
}

GLuint* Entity::getVAO()
{
	return &VAO;
}

GLuint* Entity::getVerticesVBO()
{
	return &VBO_V;
}

GLuint* Entity::getColorsVBO()
{
	return &VBO_C;
}

vector<vec3> Entity::getVertices()
{
	return vertices;
}

vector<vec4> Entity::getVerticesColors()
{
	return colors;
}

vector<vec3> Entity::getControlPointsCoordinates()
{
	return cpCoordinates;
}

vector<vec4> Entity::getControlPointsColors()
{
	return cpColors;
}

int Entity::getNumberOfVertices()
{
	return vertices.size();
}

int Entity::getNumberOfControlPoints()
{
	return nCP;
}

mat4* Entity::getModel()
{
	return &model;
}

float Entity::getShiftValue()
{
	return shiftValue;
}

float Entity::getScaleValue()
{
	return scaleValue;
}

float Entity::getRotationValue()
{
	return rotationValue;
}



Player::Player() 
{
	alive = true;
	direction = RIGHT;
}

Direction Player::getDirection()
{
	return direction;
}