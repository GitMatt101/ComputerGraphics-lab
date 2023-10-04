#version 420 core

in vec4 colore_frag;	// input: colore interpolato
out vec4 color;			// output: colore interpolato da assegnare al frammento (inalterato)

void main(){
	color = colore_frag;
}