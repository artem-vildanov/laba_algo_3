#pragma once

#include <iostream>
#include <vector>
#include "Way.h"
//#include "list_element.h"

using std::vector;

class MST 
{
	struct list_element//представление непересекающихся множеств
	{
		int value;
		int head;
	};

	int ways_amount;
	int vertices_amount;

	vector <Way> ways;//вектор путей
	vector <int> vertices;//вектор вершин
	vector <list_element> list;//список
	vector <Way> spanning_tree;//вектор, содержащий минимальное остовное дерево

public:

	MST(Graph graph);//принимает граф и информацию о нем
	
	void output_spanning_tree();//вывод остовного дерева
	void output_list();//вывод множества вершин

	vector <Way> get_spanning_tree();//геттер остовного дерева
	int get_vertices_amount();//getter of vertices amount in main graph

private:

	void MST_Kruskal();//тело алгоритма Краскала
	void _make_set(int vertex);//каждая вершина становится подмножетсвом самого себя; указатель на хэд указывает на себя;
	int _find_set(int vertex_u);//возвращает представительный элемент множества, содержащего u
	void _union(int vertex_u, int vertex_v);//объединение подмножеств
	void _sort();//сортировка путей по возрастанию весов

};

