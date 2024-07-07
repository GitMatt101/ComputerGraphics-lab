#pragma once
#include "../lib.h"

typedef enum ShadingType {
	GOURAUD,
	PHONG,
	BLINN,
	TOON,
	PASS_THROUGH,
	WAVE
};

typedef enum MaterialType {
	RED_PLASTIC,
	EMERALD,
	BRASS,
	SLATE,
	YELLOW,
	NO_MATERIAL
};

typedef struct {
	string name;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	GLfloat shininess;
} Material;

typedef enum ShaderOption {
	NONE,
	GOURAD_SHADING,
	PHONG_SHADING
};

typedef struct LightPoint {
	vec3 position;
	vec3 color;
	GLfloat power;
};

typedef struct LightShaderUniform {
	GLuint light_position_pointer;
	GLuint light_color_pointer;
	GLuint light_power_pointer;
	GLuint material_diffuse;
	GLuint material_ambient;
	GLuint material_specular;
	GLuint material_shininess;
};


#define red_plastic_ambient { 0.1f, 0.0f, 0.0f }
#define red_plastic_diffuse { 0.6, 0.1, 0.1 }
#define red_plastic_specular { 0.7, 0.6, 0.6 }
#define red_plastic_shininess 32.0f

#define brass_ambient { 0.1f, 0.06f, 0.015f }
#define brass_diffuse { 0.78, 0.57, 0.11 }
#define brass_specular { 0.99, 0.91, 0.81 }
#define brass_shininess 27.8f

#define emerald_ambient { 0.0215f, 0.04745f, 0.0215f }
#define emerald_diffuse { 0.07568, 0.61424, 0.07568 }
#define emerald_specular { 0.633, 0.727811, 0.633 }
#define emerald_shininess 78.8f

#define slate_ambient { 0.02f, 0.02f, 0.02f }
#define slate_diffuse { 0.1, 0.1, 0.1 }
#define slate_specular { 0.4, 0.4, 0.4 }
#define slate_shininess 1.78125f

#define yellow_ambient { 0.8f, 0.8f, 0.0f }
#define yellow_diffuse { 0.5,0.5,0.4 }
#define yellow_specular { 0.9,	0.9	,0.04 }
#define yellow_shininess 1.78125f
