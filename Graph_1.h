#pragma once
#include <iostream>
#include <vector>
#include "Way.h"
#include "list_element.h"

using std::cout;
using std::endl;
using std::rand;
using std::vector;

//struct list_element//������������� ���������������� ��������
//{
//	int value;
//	int head;
//	int rank;
//};

//class Way
//{	
//public:
//
//	int vertex_u;//������� u
//	int vertex_v;//������� v (������� �� ��������� � u)
//	int weight;//��� ����
//
//	Way()
//	{
//		weight = (rand() % 10) + 1;
//	}
//
//};

class Graph
{
	int ways_amount;
	int vertices_amount;

	vector <Way> ways;//������ �����
	vector <int> vertices;//������ ������

	vector <list_element> list;//������
	vector <Way> spanning_tree;//������, ���������� ����������� �������� ������
	
public:

	Graph(const int amount)
	{
		vertices_amount = amount;
		ways_amount = ((amount - 1) * amount) / 2;//����� ����� �� (amount - 1) �� 0

		for (int i = 0; i < amount; i++)
		{
			vertices.push_back(i);
		}

		Initialize_ways();
	}

	void MST_Kruskal()
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

	void get_ways()
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

	void get_spanning_tree()
	{

		cout << endl;
		cout << "===����������� �������� ������===" << endl;
		cout << endl;

		int summ = 0;
		for (int i = 0; i < spanning_tree.size(); i++)
		{
			cout << "������� U: " << spanning_tree[i].vertex_u << "\t������� v: " << spanning_tree[i].vertex_v << "\t��� ����: " << spanning_tree[i].weight << endl;
			summ += spanning_tree[i].weight;
		}

		cout << "��������� ���: " << summ << endl;
	}

	void get_list()
	{
		cout << endl;
		cout << "===��������� ������ ��������� ������===" << endl;
		cout << endl;

		for (int i = 0; i < list.size(); i++)
		{
			cout << "��������: " << list[i].value << "\t���: " << list[i].head << endl;
		}
	}

private:

	void Initialize_ways()
	{
		int available_vertices_amount = vertices_amount;
		

		for (int i = 0; i < vertices_amount; i++)
		{//������ ������������ ����� for - �������� ���� ��������� ����� ��� ������� i(i = vertex_u; i = u)

			

			available_vertices_amount--;
			
			int next_vertex = i + 1;
			for (int j = available_vertices_amount; j > 0; j--)
			{//��� i ������� ����� ������� ((����������_������ - 1) - ����������_��������_�����) ����� // j - ��� ���������� ��������� ���������� ����� ��� i �������
				Way way_buf;
				way_buf.vertex_u = i;
				way_buf.vertex_v = next_vertex;
				next_vertex++;
				ways.push_back(way_buf);//���������� ���� � ������ �����

			}
		}
	}

	void _make_set(int vertex)//������ ������� ���������� ������������� ������ ����; ��������� �� ��� ��������� �� ����; ��������� �� ����� ��������� �� ����
	{
		list_element list_element_buf;
		list_element_buf.value = vertex;
		list_element_buf.head = vertex;
		list_element_buf.rank = 1;
		list.push_back(list_element_buf);
	}

	int _find_set(int vertex_u)//���������� ���������������� ������� ���������, ����������� u
	{
		for (int i = 0; i < list.size(); ++i)
		{
			if (list[i].value == vertex_u)
				return list[i].head;
		}
	}

	void _union(int vertex_u, int vertex_v)//����������� �����������
	{


		int vertex_v_head = 0;
		int vertex_u_head = 0;
		int rank_u = 0;
		int rank_v = 0;
		

		for (int i = 0; i < list.size(); ++i)
		{
			if (list[i].value == vertex_u)
			{
				vertex_u_head = list[i].head;//������� ��� ������� u
				//cout << vertex_u_head << endl;

				rank_u = list[i].rank;//������� ����� ��������� � ������������ ������� u
			}

			if (list[i].value == vertex_v)
			{
				vertex_v_head = list[i].head;//������� ��� ������� v
				rank_v = list[i].rank;//������� ����� ��������� � ������������ ������� v
			}
		}

		if (rank_u >= rank_v)//������� ������������ ������������ � ���� ������� ������������
		{
			for (int i = 0; i < list.size(); ++i)
			{
				if (list[i].head == vertex_v_head)
				{
					list[i].head = vertex_u_head;
				}

			}
		}
		else
		{
			for (int i = 0; i < list.size(); ++i)
			{
				if (list[i].head == vertex_u_head)
				{
					list[i].head = vertex_v_head;
				}

			}
		}
		
	}


	void _sort()//���������� ����� �� ����������� �����
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

};

