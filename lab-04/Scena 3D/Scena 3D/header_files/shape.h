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
		vec4 anchor;
		float sphereRadius;
		bool selected;

	public:
		/*
		* Creates a shape with the given name and vertices.
		* 
		* @param name - The name of the shape.
		* @param vertices - The vertices thay build the shape.
		* @param sphereRadius - The radius of the sphere that contains the shape.
		*/
		Shape(char* name, vector<Vertex> vertices, float sphereRadius);

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

		/*
		* Retrieves the anchor of the shape.
		* 
		* @return The pointer to the anchor of the shape.
		*/
		vec4* getAnchor();

		/*
		* Retrieves the radius of the sphere that contains the shape.
		* 
		* @return The radius of the sphere.
		*/
		float getSphereRadius();

		/*
		* Checks if the shape is selected.
		* 
		* @return True if the shape is selected, false otherwise.
		*/
		bool isSelected();

		/*
		* If the shape is not selected, it sets selected to true, otherwise it sets it to false.
		*/
		void toggleSelection();

};