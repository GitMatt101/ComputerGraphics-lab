#include "lib.h"
#include "VAO_manager.h"

void INIT_SHAPE_VAO(Shape* shape)
{
	glGenVertexArrays(1, &shape->VAO);
	glBindVertexArray(shape->VAO);
	glGenBuffers(1, &shape->VBO_V);
	glBindBuffer(GL_ARRAY_BUFFER, shape->VBO_V);
	glBufferData(GL_ARRAY_BUFFER, shape->nVertices * sizeof(vec3), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &shape->VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, shape->VBO_C);
	glBufferData(GL_ARRAY_BUFFER, shape->nVertices * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void UPDATE_SHAPE_VAO(Shape* shape)
{
	glBindVertexArray(shape->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, shape->VBO_V);
	glBufferSubData(GL_ARRAY_BUFFER, 0, shape->nVertices * sizeof(vec3), shape->vertices.data());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, shape->VBO_C);
	glBufferSubData(GL_ARRAY_BUFFER, 0, shape->nVertices * sizeof(vec4), shape->colors.data());
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void INIT_CP_VAO(Shape* shape)
{
	glGenVertexArrays(1, &shape->VAO);
	glBindVertexArray(shape->VAO);
	glGenBuffers(1, &shape->VBO_V);
	glBindBuffer(GL_ARRAY_BUFFER, shape->VBO_V);
	glBufferData(GL_ARRAY_BUFFER, shape->nCP * sizeof(vec3), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &shape->VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, shape->VBO_C);
	glBufferData(GL_ARRAY_BUFFER, shape->nCP * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void UPDATE_CP_VAO(Shape* shape)
{
	glBindVertexArray(shape->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, shape->VBO_V);
	glBufferSubData(GL_ARRAY_BUFFER, 0, shape->cpCoordinates.size() * sizeof(vec3), shape->cpCoordinates.data());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, shape->VBO_C);
	glBufferSubData(GL_ARRAY_BUFFER, 0, shape->cpColors.size() * sizeof(vec4), shape->cpColors.data());
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}