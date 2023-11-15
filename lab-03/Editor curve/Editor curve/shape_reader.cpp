#include "shape_reader.h"
#include "lib.h"

#define MAX_DATA 1000	// Numero massimo di vertici da poter memorizzare

typedef struct
{
	float x;
	float y;
	float z;
} Vertex;

void create_shape_from_file(char* file_name, Shape* shape, Shape* d)
{
	FILE* file = fopen(file_name, "r");
	if (file == NULL)
		perror("Impossibile aprire il file");

	vector<Vertex> data;	// Vettore per memorizzare i vertici della figura

	float x, y, z;
	for (int riga = 0; fscanf(file, "%f %f %f", &x, &y, &z) == 3 && riga < MAX_DATA; riga++)
		data.push_back({x, y, z});

	fclose(file);		// Chiudi il file

	// Assegna i dati ai control point della Curva
	for (int i = 0; i < data.size(); i++)
	{
		shape->cpCoordinates.push_back(vec3(data[i].x, data[i].y, data[i].z));
		d->cpCoordinates.push_back(vec3(0.0f, 0.0f, 0.0f));
	}
}