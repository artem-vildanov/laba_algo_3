#pragma once

using std::rand;

class Way
{
public:
	//вершина u
	int vertex_u;

	//вершина v (смежная по отношению к u)
	int vertex_v;

	//вес пути
	int weight;

	Way()
	{
		weight = (rand() % 100) + 1;
	}

};