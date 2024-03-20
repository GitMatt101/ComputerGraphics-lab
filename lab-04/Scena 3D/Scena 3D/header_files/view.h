#pragma once
#include "../lib.h"

struct View {
	vec4 position;
	vec4 target;
	vec4 upVector;
	vec4 direction;
};

struct Perspective {
	float fov;			// Field of View
	float aspect;
	float nearPlane;
	float farPlane;
};

struct Character {
	unsigned int textureID; // ID handle of the glyph texture
	ivec2 size;				// Size of glyph
	ivec2 Bearing;			// Offset from baseline to left/top of glyph
	unsigned int advance;   // Horizontal offset to advance to next glyph
};