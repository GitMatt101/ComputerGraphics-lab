#version 330 core

layout(location = 0) in vec3 aPos;		// 0 = coordinate posizionali
layout(location = 1) in vec4 Color;		// 1 = colori

out vec4 colore_frag;					// output: colore interpolato

void main(){	
	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);
	colore_frag = Color;
}

