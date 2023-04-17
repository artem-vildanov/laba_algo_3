#include <iostream>
#include "Graph.h"
#include "MST.h"
//#include "list_element.h"

#pragma once
#ifndef _EXAMPLE_MST_CPP_
#define _EXAMPLE_MST_CPP_

using std::cout;
using std::endl;
using std::rand;
using std::vector;

MST::MST(Graph graph)
{
	ways_amount = graph.get_ways_amount();
	vertices_amount = graph.get_vertices_amount();
	ways = graph.get_ways();
	vertices = graph.get_vertices();

	MST_Kruskal();//create MST from input graph
}

void MST::MST_Kruskal()
{

	for (int i = 0; i < vertices_amount; ++i)
	{
		_make_set(vertices[i]);//������� u ���������� � �� ����������� ������������
	}

	_sort();//����� ways ����������� �� ����������� �� ����� weight

	for (int i = 0; i < ways_amount; i++)
	{
		if (_find_set(ways[i].vertex_u) != _find_set(ways[i].vertex_v))//�������� ��������� ����� ������� u � v
		{
			spanning_tree.push_back(ways[i]);
			_union(ways[i].vertex_u, ways[i].vertex_v);//����������� ���������������� ����������� u � v
		}
	}

}

void MST::output_spanning_tree()
{

	cout << endl;
	cout << "===����������� �������� ������===" << endl;

	int summ = 0;
	for (int i = 0; i < spanning_tree.size(); i++)
	{
		cout << "������� U: " << spanning_tree[i].vertex_u << "\t������� v: " << spanning_tree[i].vertex_v << "\t��� ����: " << spanning_tree[i].weight << endl;
		summ += spanning_tree[i].weight;
	}

	cout << "��������� ���: " << summ << endl;
}

void MST::output_list()
{
	cout << endl;
	cout << "===��������� ������ ��������� ������===" << endl;

	for (int i = 0; i < list.size(); i++)
	{
		cout << "��������: " << list[i].value << "\t���: " << list[i].head << endl;
	}
}

void MST::_make_set(int vertex)//������ ������� ���������� ������������� ������ ����; ��������� �� ��� ��������� �� ����; ��������� �� ����� ��������� �� ����
{
	list_element list_element_buf;
	list_element_buf.value = vertex;
	list_element_buf.head = vertex;
	list.push_back(list_element_buf);
}

int MST::_find_set(int vertex_u)//���������� ���������������� ������� ���������, ����������� u
{
	for (int i = 0; i < list.size(); ++i)
	{
		if (list[i].value == vertex_u)
			return list[i].head;
	}
}

void MST::_union(int vertex_u, int vertex_v)//����������� �����������
{


	int vertex_v_head = 0;
	int vertex_u_head = 0;


	for (int i = 0; i < list.size(); ++i)
	{
		if (list[i].value == vertex_u)
		{
			vertex_u_head = list[i].head;//������� ��� ������� u
			//cout << vertex_u_head << endl;

			
		}

		if (list[i].value == vertex_v)
		{
			vertex_v_head = list[i].head;//������� ��� ������� v
			
		}
	}

	
	
	for (int i = 0; i < list.size(); ++i)
	{
		if (list[i].head == vertex_v_head)
		{
				list[i].head = vertex_u_head;
		}

	}
	


}

void MST::_sort()//���������� ����� �� ����������� �����
{
	int i, j, step, comp = 0;

	for (step = 1; step <= ways.size() / 9; step = step * 3 + 1);

	while (step >= 1)
	{
		for (i = step; i < ways.size(); i++)
		{
			comp++;
			for (j = i - step; j >= 0 && ways[j].weight > ways[j + step].weight; j -= step)
			{
				std::swap(ways[j], ways[j + step]);
				//comp++;
			}
		}
		step = (step - 1) / 3;
	}
}

vector <Way> MST::get_spanning_tree()
{
	return spanning_tree;
}

int MST::get_vertices_amount()
{
	return vertices_amount;
}

#endif