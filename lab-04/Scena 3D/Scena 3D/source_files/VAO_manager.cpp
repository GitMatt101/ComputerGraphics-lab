#include "../header_files/VAO_manager.h"

void initShapeVAO(Shape* shape) {
	vector<vec3> vertices;
	vector<vec4> colors;
	for (const Vertex& vertex : *shape->getVertices()) {
		vertices.push_back(vertex.coordinates);
		colors.push_back(vertex.color);
	}

	glGenVertexArrays(1, shape->getVAO());
	glBindVertexArray(*shape->getVAO());
	glGenBuffers(1, shape->getVerticesVBO());
	glBindBuffer(GL_ARRAY_BUFFER, *shape->getVerticesVBO());
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, shape->getColorsVBO());
	glBindBuffer(GL_ARRAY_BUFFER, *shape->getColorsVBO());
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec4), colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, shape->getEBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *shape->getEBO());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape->getIndexes()->size() * sizeof(GLuint), shape->getIndexes()->data(), GL_STATIC_DRAW);
}

void initTextVAO(GLuint* textVAO, GLuint* textVBO) {
	glGenVertexArrays(1, textVAO);
	glGenBuffers(1, textVBO);
	glBindVertexArray(*textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, *textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}