#include "../header_files/geometry.h"

pair<vector<Vertex>, vector<GLuint>> createCuboid(float width, float height, float depth, vec4 color1, vec4 color2) {
	float x = width / 2;
	float y = height / 2;
	float z = depth / 2;

	vector<Vertex> vertices;

	// Front
	vertices.push_back(Vertex(vec3(-x, y, z), color1));
	vertices.push_back(Vertex(vec3(x, y, z), color2));
	vertices.push_back(Vertex(vec3(x, -y, z), color1));
	vertices.push_back(Vertex(vec3(-x, -y, z), color2));

	// Back
	vertices.push_back(Vertex(vec3(-x, y, -z), color1));
	vertices.push_back(Vertex(vec3(x, y, -z), color2));
	vertices.push_back(Vertex(vec3(x, -y, -z), color1));
	vertices.push_back(Vertex(vec3(-x, -y, -z), color2));

	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f)));

	// Indexes
	vector<GLuint> indexes;
	indexes.push_back(0); indexes.push_back(1); indexes.push_back(2);
	indexes.push_back(2); indexes.push_back(3); indexes.push_back(0);
	indexes.push_back(1); indexes.push_back(5); indexes.push_back(6);
	indexes.push_back(6); indexes.push_back(2); indexes.push_back(1);
	indexes.push_back(7); indexes.push_back(6); indexes.push_back(5);
	indexes.push_back(5); indexes.push_back(4); indexes.push_back(7);
	indexes.push_back(4); indexes.push_back(0); indexes.push_back(3);
	indexes.push_back(3); indexes.push_back(7); indexes.push_back(4);
	indexes.push_back(4); indexes.push_back(5); indexes.push_back(1);
	indexes.push_back(1); indexes.push_back(0); indexes.push_back(4);
	indexes.push_back(3); indexes.push_back(2); indexes.push_back(6);
	indexes.push_back(6); indexes.push_back(7); indexes.push_back(3);
	indexes.push_back(vertices.size() - 1);

	return pair<vector<Vertex>, vector<GLuint>>(vertices, indexes);
}

pair<vector<Vertex>, vector<GLuint>> createEllipsoid(float rx, float ry, float rz, int precision, vec4 color1, vec4 color2) {
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
			vertices.push_back(Vertex(vec3(x, y, z), color1));
		}
	}
	vertices.push_back(Vertex(center, color2));

	vector<GLuint> indexes;
	for (int i = 0; i < precision * precision + precision; ++i) {
		indexes.push_back(i);
		indexes.push_back(i + precision + 1);
		indexes.push_back(i + precision);
		indexes.push_back(i + precision + 1);
		indexes.push_back(i);
		indexes.push_back(i + 1);
	}
	indexes.push_back(vertices.size() - 1);

	return pair<vector<Vertex>, vector<GLuint>>(vertices, indexes);
}

pair<vector<Vertex>, vector<GLuint>> createPyramid(float width, float height, float depth, vec4 color1, vec4 color2) {
	float x = width / 2;
	float y = height / 2;
	float z = depth / 2;

	vector<Vertex> vertices;

	// Base
	vertices.push_back(Vertex(vec3(-x, -y, z), color1));
	vertices.push_back(Vertex(vec3(x, -y, z), color1));
	vertices.push_back(Vertex(vec3(x, -y, -z), color1));
	vertices.push_back(Vertex(vec3(-x, -y, -z), color1));

	// Punta
	vertices.push_back(Vertex(vec3(0.0f, y, 0.0f), color2));

	vector<GLuint> indexes;
	indexes.push_back(0); indexes.push_back(1); indexes.push_back(2);
	indexes.push_back(0); indexes.push_back(2); indexes.push_back(3);
	indexes.push_back(0); indexes.push_back(4); indexes.push_back(3);
	indexes.push_back(0); indexes.push_back(1); indexes.push_back(4);
	indexes.push_back(3); indexes.push_back(2); indexes.push_back(4);
	indexes.push_back(1); indexes.push_back(2); indexes.push_back(4);

	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	indexes.push_back(vertices.size() - 1);

	return pair<vector<Vertex>, vector<GLuint>>(vertices, indexes);
}