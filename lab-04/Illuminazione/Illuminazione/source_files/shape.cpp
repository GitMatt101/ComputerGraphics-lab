#include "../header_files/shape.h"

Shape::Shape(string name, vector<Vertex> vertices, vector<GLuint> indexes, vector<vec3> normals, ShadingType shading, MaterialType material, float sphereRadius) {
	this->name = name;
	this->vertices = vertices;
	this->indexes = indexes;
	this->normals = normals;
	this->shading = shading;
	this->material = material;
	this->selected = false;
	this->sphereRadius = sphereRadius;
	this->model = mat4(1.0f);
	this->anchorObj = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	this->anchorWorld = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

string Shape::getName() {
	return this->name;
}

vector<Vertex>* Shape::getVertices() {
	return &(this->vertices);
}

vector<GLuint>* Shape::getIndexes() {
	return &(this->indexes);
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

vec4* Shape::getAnchorObj() {
	return &(this->anchorObj);
}

vec4* Shape::getAnchorWorld() {
	return &(this->anchorWorld);
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

ShadingType Shape::getShading() {
	return this->shading;
}

MaterialType Shape::getMaterial() {
	return this->material;
}

void Shape::setShading(ShadingType shading) {
	this->shading = shading;
}

void Shape::setMaterial(MaterialType material) {
	this->material = material;
}

vector<vec3>* Shape::getNormals() {
	return &(this->normals);
}

GLuint* Shape::getNormalsVBO() {
	return &(this->VBO_N);
}