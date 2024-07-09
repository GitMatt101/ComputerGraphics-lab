#pragma once
#include "../lib.h"

// A vertex is defined by its coordinates and its color.
struct Vertex {
	vec3 coordinates;
	vec4 color;

	/*
	* Creates a vertex with the given parameters.
	* 
	* @param coordinates - The coordinates of the vertex.
	* @param color - The color of the vertex.
	*/
	Vertex(const vec3& coordinates, const vec4& color) : coordinates(coordinates), color(color) {
		this->coordinates = coordinates;
		this->color = color;
	}

	// Creates a Vertex with coordinates (0, 0, 0) and color black.
	Vertex() {
		this->coordinates = vec3(0.0f, 0.0f, 0.0f);
		this->color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
};

void createCuboid(float width, float height, float depth, vec4 color1, vec4 color2, vector<Vertex>* vertices, vector<GLuint>* indices);

void createEllipsoid(float rx, float ry, float rz, int precision, vec4 color, vector<Vertex>* vertices, vector<GLuint>* indices, vector<vec3>* normals, vector<vec2>* textureCoordinates);

pair<vector<Vertex>, vector<GLuint>> createPyramid(float width, float height, float depth, vec4 color1, vec4 color2);