#pragma once
#include <random>


class Coordinate_vertex
{
public:

	int vertex;

	double Y_coord = -1;
	double X_coord = -1;

	Coordinate_vertex()
	{
		Y_coord = (rand() % 100) + 1;
		X_coord = (rand() % 100) + 1;
	}
};

