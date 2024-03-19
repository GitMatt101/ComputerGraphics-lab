#pragma once
#include "../lib.h"
#include "geometry.h"

// Class used to model a generic 3D shape.
class Shape {

	private:
		char* name;
		vector<Vertex> vertices;
		mat4 model;
		GLuint VAO;
		GLuint VBO_V;
		GLuint VBO_C;
		GLuint EBO;

	public:
		/*
		* Creates a shape with the given name and vertices.
		* 
		* @param name - The name of the shape.
		* @param vertices - The vertices thay build the shape.
		*/
		Shape(char* name, vector<Vertex> vertices);

		/*
		* Retrieves the name of the shape.
		* 
		* @return The name of the shape.
		*/
		char* getName();

		/*
		* Retrieves the vertices of the shape.
		* 
		* @return The pointer to the vertices of the shape.
		*/
		vector<Vertex>* getVertices();

		/*
		* Retrieves the model matrix of the shape.
		* 
		* @return The pointer to the model matrix of the shape.
		*/
		mat4* getModel();

		/*
		* Retrieves the VAO of the shape.
		* 
		* @return The pointer to the VAO of the shape.
		*/
		GLuint* getVAO();

		/*
		* Retrieves the VBO of the vertices of the shape.
		*
		* @return The pointer to the VBO of the vertices the shape.
		*/
		GLuint* getVerticesVBO();

		/*
		* Retrieves the VBO of the colors the shape.
		*
		* @return The pointer to the VBO of the colors of the shape.
		*/
		GLuint* getColorsVBO();

		/*
		* Retrieves the EBO of the shape.
		*
		* @return The pointer to the EBO of the shape.
		*/
		GLuint* getEBO();

};