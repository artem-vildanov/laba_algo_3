#include <iostream>
#include "Graph.h"
#include "Coordinates.h"

#pragma once
#ifndef _EXAMPLE_GRAPH_CPP_
#define _EXAMPLE_GRAPH_CPP_

using std::cout;
using std::endl;
using std::rand;
using std::vector;


Graph::Graph(int amount)
{
	vertices_amount = amount;
	ways_amount = ((amount - 1) * amount) / 2;//����� ����� �� (amount - 1) �� 0

	for (int i = 1; i < amount + 1; i++)
	{
		vertices.push_back(i);
	}

	Initialize_ways();
}

void Graph::output_ways()
{
	cout << endl;
	cout << "===����������� ����===" << endl;
	cout << endl;

	for (int i = 0; i < ((vertices_amount - 1) * vertices_amount) / 2; i++)
	{
		cout << "������� U: " << ways[i].vertex_u << "\t������� v: " << ways[i].vertex_v << "\t��� ����: " << ways[i].weight << endl;
		if (ways.back().vertex_u == ways[i].vertex_u || ways[i].vertex_u != ways[i + 1].vertex_u)
			cout << endl;
	}
}

//������ ����
void Graph::Initialize_ways()
{
	int available_vertices_amount = vertices_amount;

	for (int i = 1; i < vertices_amount + 1; i++)
	{//������ ������������ ����� for - �������� ���� ��������� ����� ��� ������� i(i = vertex_u; i = u)

		available_vertices_amount--;
		int next_vertex = i + 1;

		Coordinate_vertex new_coordinate;
		new_coordinate.vertex = i;
		coordinates.push_back(new_coordinate);//���������� ������� ��������� (���������� + ������ �������)

		for (int j = available_vertices_amount; j > 0; j--)
		{//��� i ������� ����� ������� ((����������_������ - 1) - ����������_��������_�����) ����� // j - ��� ���������� ��������� ���������� ����� ��� i �������
			
			Way way_buf;
			way_buf.vertex_u = i;
			way_buf.vertex_v = next_vertex;
			next_vertex++;
			ways.push_back(way_buf);//���������� ���� � ������ �����

		}
	}

	//��������� ������ ����� � ������ ��������� ������
	
	//������������ ����� �����
	for (int i = 0; i < ways.size(); ++i)
	{
		int Y_coord_u = -1;
		int Y_coord_v = -1;

		int X_coord_u = -1;
		int X_coord_v = -1;

		for (int j = 0; j < coordinates.size(); j++)//����� ���������� ������� u
		{
			if (coordinates[j].vertex == ways[i].vertex_u)
			{
				Y_coord_u = coordinates[j].Y_coord;
				X_coord_u = coordinates[j].X_coord;
			}
		}

		for (int j = 0; j < coordinates.size(); j++)//����� ���������� ������� v
		{
			if (coordinates[j].vertex == ways[i].vertex_v)
			{
				Y_coord_v = coordinates[j].Y_coord;
				X_coord_v = coordinates[j].X_coord;
			}
		}

		ways[i].weight = sqrt((X_coord_u - X_coord_v) * (X_coord_u - X_coord_v) + (Y_coord_u - Y_coord_v) * (Y_coord_u - Y_coord_v));
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

vector <Coordinate_vertex> Graph::get_coordinates()
{
	return coordinates;
}


#endif