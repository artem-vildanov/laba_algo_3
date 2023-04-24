#pragma once
#include "Coordinates.h"
#include <vector>
#include <math.h>

using std::vector;

class Way
{
public:
	//вершина u
	int vertex_u = -1;

	//вершина v (смежная по отношению к u)
	int vertex_v = -1;

	//вес пути
	int weight = -1;

	//void generate_weight(Way ways)
	//{
	//	int Y_coord_u;
	//	int Y_coord_v;
	//	int X_coord_u;
	//	int X_coord_v;
	//	for (int i = 0; i < coordinates.size(); i++)//поиск координаты вершины u
	//	{
	//		if (coordinates[i].vertex == ways.vertex_u)
	//		{
	//			Y_coord_u = coordinates[i].Y_coord;
	//			X_coord_u = coordinates[i].X_coord;
	//		}
	//	}
	//	for (int i = 0; i < coordinates.size(); i++)//поиск координаты вершины v
	//	{
	//		if (coordinates[i].vertex == ways.vertex_v)
	//		{
	//			Y_coord_v = coordinates[i].Y_coord;
	//			X_coord_v = coordinates[i].X_coord;
	//		}
	//	}
	//	weight = sqrt((X_coord_u - X_coord_v) * (X_coord_u - X_coord_v) + (Y_coord_u - Y_coord_v) * (Y_coord_u - Y_coord_v));
	//}

};