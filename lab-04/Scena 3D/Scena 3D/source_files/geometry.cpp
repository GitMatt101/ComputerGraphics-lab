#include "../header_files/geometry.h"

vector<Vertex> createCuboid(float width, float height, float depth, vec4 color) {
	float x = width / 2;
	float y = height / 2;
	float z = depth / 2;

	vector<Vertex> vertices;

	// Faccia anteriore
	vertices.push_back(Vertex(vec3(-x, y, z), color));
	vertices.push_back(Vertex(vec3(x, y, z), color));
	vertices.push_back(Vertex(vec3(x, -y, z), color));
	vertices.push_back(Vertex(vec3(-x, -y, z), color));

	// Faccia posteriore
	vertices.push_back(Vertex(vec3(-x, y, -z), color));
	vertices.push_back(Vertex(vec3(x, y, -z), color));
	vertices.push_back(Vertex(vec3(x, -y, -z), color));
	vertices.push_back(Vertex(vec3(-x, -y, -z), color));

	return vertices;
}

vector<Vertex> createEllipsoid(float rx, float ry, float rz, int precision, vec4 color) {
	vec3 center = vec3(0.0f, 0.0f, 0.0f);

	vector<Vertex> vertices;

	for (int i = 0; i < precision; i++) {
		float step1 = i / (float)precision;
		float phi = step1 * PI;

		for (int j = 0; j < precision; j++) {
			float step2 = j / (float)precision;
			float theta = step2 * PI * 2;

			float x = center.x + rx * (cosf(theta) * sinf(phi));
			float y = center.y + ry * cosf(phi);
			float z = center.z + rz * sinf(theta) * sinf(phi);
			vertices.push_back(Vertex(vec3(x, y, z), color));
		}
	}

	return vertices;
}

vector<Vertex> createPyramid(float width, float height, float depth, vec4 color) {
	float x = width / 2;
	float y = height / 2;
	float z = depth / 2;

	vector<Vertex> vertices;

	// Base
	vertices.push_back(Vertex(vec3(-x, -y, z), color));
	vertices.push_back(Vertex(vec3(x, -y, z), color));
	vertices.push_back(Vertex(vec3(x, -y, -z), color));
	vertices.push_back(Vertex(vec3(-x, -y, -z), color));

	// Punta
	vertices.push_back(Vertex(vec3(0.0f, y, 0.0f), color));

	return vertices;
}