#pragma once

#include <iostream>
#include <vector>
#include "Way.h"
//#include "list_element.h"

using std::vector;

class MST 
{
	struct list_element//������������� ���������������� ��������
	{
		int value;
		int head;
	};

	int ways_amount;
	int vertices_amount;

	vector <Way> ways;//������ �����
	vector <int> vertices;//������ ������
	vector <list_element> list;//������
	vector <Way> spanning_tree;//������, ���������� ����������� �������� ������

public:

	MST(Graph graph);//��������� ���� � ���������� � ���
	
	void output_spanning_tree();//����� ��������� ������
	void output_list();//����� ��������� ������

	vector <Way> get_spanning_tree();//������ ��������� ������
	int get_vertices_amount();//getter of vertices amount in main graph

private:

	void MST_Kruskal();//���� ��������� ��������
	void _make_set(int vertex);//������ ������� ���������� ������������� ������ ����; ��������� �� ��� ��������� �� ����;
	int _find_set(int vertex_u);//���������� ���������������� ������� ���������, ����������� u
	void _union(int vertex_u, int vertex_v);//����������� �����������
	void _sort();//���������� ����� �� ����������� �����

};

