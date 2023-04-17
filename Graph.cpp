#include <iostream>
#include "Graph.h"

#pragma once
#ifndef _EXAMPLE_GRAPH_CPP_
#define _EXAMPLE_GRAPH_CPP_

using std::cout;
using std::endl;
using std::rand;
using std::vector;

Graph::Graph() {}

Graph::Graph(int amount)
{
	vertices_amount = amount;
	ways_amount = ((amount - 1) * amount) / 2;//сумма чисел от (amount - 1) до 0

	for (int i = 1; i < amount + 1; i++)
	{
		vertices.push_back(i);
	}

	Initialize_ways();
}

void Graph::output_ways()
{
	cout << endl;
	cout << "===Изначальный граф===" << endl;
	cout << endl;

	for (int i = 0; i < ((vertices_amount - 1) * vertices_amount) / 2; i++)
	{
		cout << "Вершина U: " << ways[i].vertex_u << "\tВершина v: " << ways[i].vertex_v << "\tВес пути: " << ways[i].weight << endl;
		if (ways.back().vertex_u == ways[i].vertex_u || ways[i].vertex_u != ways[i + 1].vertex_u)
			cout << endl;
	}
}

int Graph::get_ways_amount()
{
	return ways_amount;
}

int Graph::get_vertices_amount()
{
	return vertices_amount;
}

vector <Way> Graph::get_ways()
{
	return ways;
}

vector <int> Graph::get_vertices()
{
	return vertices;
}

//полный граф
void Graph::Initialize_ways()
{
	int available_vertices_amount = vertices_amount;


	for (int i = 1; i < vertices_amount + 1; i++)
	{//каждое срабатывание цикла for - создание всех возможных путей для вершины i(i = vertex_u; i = u)

		available_vertices_amount--;
		int next_vertex = i + 1;

		for (int j = available_vertices_amount; j > 0; j--)
		{//для i вершины будет создано ((количество_вершин - 1) - количество_входящих_путей) путей // j - это количество доступных уникальных путей для i вершины
			Way way_buf;
			way_buf.vertex_u = i;
			way_buf.vertex_v = next_vertex;
			next_vertex++;
			ways.push_back(way_buf);//добавление пути в массив путей

		}
	}
}

#endif