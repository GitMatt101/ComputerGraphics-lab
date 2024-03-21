#include "../header_files/shape.h"

Shape::Shape(char* name, vector<Vertex> vertices, float sphereRadius) {
	this->name = name;
	this->vertices = vertices;
	this->selected = false;
	this->sphereRadius = sphereRadius;
}

char* Shape::getName() {
	return this->name;
}

vector<Vertex>* Shape::getVertices() {
	return &(this->vertices);
}

mat4* Shape::getModel() {
	return &(this->model);
}

GLuint* Shape::getVAO() {
	return &(this->VAO);
}

GLuint* Shape::getVerticesVBO() {
	return &(this->VBO_V);
}

GLuint* Shape::getColorsVBO() {
	return &(this->VBO_C);
}

GLuint* Shape::getEBO() {
	return &(this->EBO);
}

vec4* Shape::getAnchor() {
	return &(this->anchor);
}

float Shape::getSphereRadius() {
	return this->sphereRadius;
}

bool Shape::isSelected() {
	return this->selected;
}

void Shape::toggleSelection() {
	this->selected = !this->selected;
}