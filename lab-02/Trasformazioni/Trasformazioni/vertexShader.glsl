#version 330 core

layout (location = 0) in vec3 aPos;		// 0 = coordinate posizionali
layout (location = 1) in vec4 Color;	// 1 = colori

out vec4 colore_frag;					// output: colore interpolato

// Il tipo 'uniform' indica una variabile input dello shader che è costante durante la chiamata glDraw
uniform mat4 Projection;
uniform mat4 Model;

void main(){	
	gl_Position = Projection * Model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	colore_frag = Color;
}