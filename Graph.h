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

	Graph(const int amount);//конструктор с параметром "количество вершин", определяющий количество путей и вызывающий init
	void output_ways();//вывод путей

	int get_ways_amount();//гетер количества путей
	int get_vertices_amount();//гетер количества вершин
	vector <Way> get_ways();//гетер массива путей
	vector <int> get_vertices();//гетер массива вершин

	vector <Coordinate_vertex> get_coordinates();

private:

	//заполнение массива путей, инициализация путей весами
	void Initialize_ways();

protected:

	int ways_amount;
	int vertices_amount;

	vector <Way> ways;//вектор путей
	vector <int> vertices;//вектор вершин
	vector <Coordinate_vertex> coordinates;//вектор координат вершин

};

#endif