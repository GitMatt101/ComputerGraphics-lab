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

/*
* Creates a cuboid shape in 3D.
* 
* @param width - The width of the shape.
* @param height - The height of the shape.
* @param depth - The depth of the shape.
* @param color - The color of the shape.
* @return A vector of vertices.
*/
vector<Vertex> createCuboid(float width, float height, float depth, vec4 color);

/*
* Creates an ellipsoid shape in 3D.
* 
* @param rx - The x component of the radius (width).
* @param ry - The y component of the radius (height).
* @param rz - The z component of the radius (depth).
* @param precision - Defines the smoothness of the shape (higher precision means smoother surface).
* @param color - The color of the shape.
* @return A vector of vertices.
*/
vector<Vertex> createEllipsoid(float rx, float ry, float rz, int precision, vec4 color);

/*
* Creates a pyramid shape in 3D.
*
* @param rx - The x component of the radius (width).
* @param ry - The y component of the radius (height).
* @param rz - The z component of the radius (depth).
* @param color - The color of the shape.
* @return A vector of vertices.
*/
vector<Vertex> createPyramid(float width, float height, float depth, vec4 color);