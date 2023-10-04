#version 420 core

in vec4 colore_frag;		// input: colore interpolato da assegnare al frammento
out vec4 color;				// output: colore ricevuto in input (inalterato)

void main(){
	color = colore_frag;	// Assegno al pixel il colore interpolato
}