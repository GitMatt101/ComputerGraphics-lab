#include "../header_files/shape.h"

Shape::Shape(char* name, vector<Vertex> vertices) {
	this->name = name;
	this->vertices = vertices;
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