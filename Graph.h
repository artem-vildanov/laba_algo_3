#pragma once
#ifndef EXAMPLE_H
#define EXAMPLE_H

#pragma once
#include <iostream>
#include <vector>
#include "Way.h"
#include "list_element.h"

using std::vector;

class Graph
{

public:

	Graph();
	Graph(const int amount);//����������� � ���������� "���������� ������", ������������ ���������� ����� � ���������� init
	void output_ways();//����� �����

	int get_ways_amount();//����� ���������� �����
	int get_vertices_amount();//����� ���������� ������
	vector <Way> get_ways();//����� ������� �����
	vector <int> get_vertices();//����� ������� ������

private:

	//���������� ������� �����, ������������� ����� ������
	void Initialize_ways();

protected:

	int ways_amount;
	int vertices_amount;

	//������ �����
	vector <Way> ways;

	vector <int> vertices;//������ ������
};

#endif