#pragma once
#include "../lib.h"
#include "shape.h"

/*
* Initializes the VAO of a given shape.
* 
* @param shape - The shape.
*/
void initShapeVAO(Shape* shape);

/*
* Initializes the text VAO of the program.
*
* @param textVAO - The text VAO.
* @param textVBO - The text VBO.
*/
void initTextVAO(GLuint* textVAO, GLuint* textVBO);