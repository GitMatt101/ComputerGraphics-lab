#include "lib.h"
#include "VAO_manager.h"
#include "entities.h"
#include <iostream>
using namespace std;

void initShapeVAO(Entity* entity)
{
	glGenVertexArrays(1, entity->getVAO());
	glBindVertexArray(*entity->getVAO());
	glGenBuffers(1, entity->getVerticesVBO());
	glBindBuffer(GL_ARRAY_BUFFER, *entity->getVerticesVBO());
	glBufferData(GL_ARRAY_BUFFER, entity->getNumberOfVertices() * sizeof(vec3), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, entity->getColorsVBO());
	glBindBuffer(GL_ARRAY_BUFFER, *entity->getColorsVBO());
	glBufferData(GL_ARRAY_BUFFER, entity->getNumberOfVertices() * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void updateShapeVAO(Entity* entity)
{
	glBindVertexArray(*entity->getVAO());
	glBindBuffer(GL_ARRAY_BUFFER, *entity->getVerticesVBO());
	glBufferSubData(GL_ARRAY_BUFFER, 0, entity->getNumberOfVertices() * sizeof(vec3), entity->getVertices().data());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, *entity->getColorsVBO());
	glBufferSubData(GL_ARRAY_BUFFER, 0, entity->getNumberOfVertices() * sizeof(vec4), entity->getVerticesColors().data());
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void initControlPointsVAO(Entity* entity)
{
	glGenVertexArrays(1, entity->getVAO());
	glBindVertexArray(*entity->getVAO());
	glGenBuffers(1, entity->getVerticesVBO());
	glBindBuffer(GL_ARRAY_BUFFER, *entity->getVerticesVBO());
	glBufferData(GL_ARRAY_BUFFER, entity->getNumberOfControlPoints() * sizeof(vec3), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, entity->getColorsVBO());
	glBindBuffer(GL_ARRAY_BUFFER, *entity->getColorsVBO());
	glBufferData(GL_ARRAY_BUFFER, entity->getNumberOfControlPoints() * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void updateControlPointsVAO(Entity* entity)
{
	glBindVertexArray(*entity->getVAO());
	glBindBuffer(GL_ARRAY_BUFFER, *entity->getVerticesVBO());
	glBufferSubData(GL_ARRAY_BUFFER, 0, entity->getControlPointsCoordinates().size() * sizeof(vec3), entity->getControlPointsCoordinates().data());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, *entity->getColorsVBO());
	glBufferSubData(GL_ARRAY_BUFFER, 0, entity->getControlPointsColors().size() * sizeof(vec4), entity->getControlPointsColors().data());
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}