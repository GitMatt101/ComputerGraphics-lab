#pragma once
#include "../lib.h"
#include "geometry.h"
#include "light_materials.hpp"

// Class used to model a generic 3D shape.
class Shape {

	private:
		string name;
		vector<Vertex> vertices;
		vector <GLuint> indexes;
		vector<vec3> normals;
		mat4 model;
		GLuint VAO;
		GLuint VBO_V;
		GLuint VBO_C;
		GLuint VBO_N;
		GLuint EBO;
		ShadingType shading;
		MaterialType material;
		vec4 anchorObj;
		vec4 anchorWorld;
		float sphereRadius;
		bool selected;

	public:
		Shape(string name, vector<Vertex> vertices, vector<GLuint> indexes, vector<vec3> normals, ShadingType shading, MaterialType material, float sphereRadius);
		string getName();
		vector<Vertex>* getVertices();
		vector<GLuint>* getIndexes();
		vector<vec3>* getNormals();
		mat4* getModel();
		GLuint* getVAO();
		GLuint* getVerticesVBO();
		GLuint* getColorsVBO();
		GLuint* getNormalsVBO();
		GLuint* getEBO();
		vec4* getAnchorObj();
		vec4* getAnchorWorld();
		ShadingType getShading();
		MaterialType getMaterial();
		void setShading(ShadingType shading);
		void setMaterial(MaterialType material);
		float getSphereRadius();
		bool isSelected();
		void toggleSelection();

};