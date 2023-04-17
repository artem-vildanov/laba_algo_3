#pragma once
#include <iostream>
#include <vector>
#include "Way.h"
#include "list_element.h"

using std::cout;
using std::endl;
using std::rand;
using std::vector;

//struct list_element//представление непересекающихся множеств
//{
//	int value;
//	int head;
//	int rank;
//};

//class Way
//{	
//public:
//
//	int vertex_u;//вершина u
//	int vertex_v;//вершина v (смежная по отношению к u)
//	int weight;//вес пути
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

	vector <Way> ways;//вектор путей
	vector <int> vertices;//вектор вершин

	vector <list_element> list;//список
	vector <Way> spanning_tree;//вектор, содержащий минимальное остовное дерево
	
public:

	Graph(const int amount)
	{
		vertices_amount = amount;
		ways_amount = ((amount - 1) * amount) / 2;//сумма чисел от (amount - 1) до 0

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
			_make_set(vertices[i]);//вершина u помещается в ее собственное подмножество
		}

		_sort();//ребра ways сортируются по возрастанию их весов weight

		for (int i = 0; i < ways_amount; i++)
		{
			if (_find_set(ways[i].vertex_u) != _find_set(ways[i].vertex_v))//проверка равенства хэдов вершины u и v
			{
				spanning_tree.push_back(ways[i]);
				_union(ways[i].vertex_u, ways[i].vertex_v);//объединение непересекающихся подмножеств u и v
			}
		}

	}

	void get_ways()
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

	void get_spanning_tree()
	{

		cout << endl;
		cout << "===Минимальное остовное дерево===" << endl;
		cout << endl;

		int summ = 0;
		for (int i = 0; i < spanning_tree.size(); i++)
		{
			cout << "Вершина U: " << spanning_tree[i].vertex_u << "\tВершина v: " << spanning_tree[i].vertex_v << "\tВес пути: " << spanning_tree[i].weight << endl;
			summ += spanning_tree[i].weight;
		}

		cout << "Суммарный вес: " << summ << endl;
	}

	void get_list()
	{
		cout << endl;
		cout << "===Множество вершин остовного дерева===" << endl;
		cout << endl;

		for (int i = 0; i < list.size(); i++)
		{
			cout << "Значение: " << list[i].value << "\tХед: " << list[i].head << endl;
		}
	}

private:

	void Initialize_ways()
	{
		int available_vertices_amount = vertices_amount;
		

		for (int i = 0; i < vertices_amount; i++)
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

	void _make_set(int vertex)//каждая вершина становится подмножетсвом самого себя; указатель на хэд указывает на себя; указатель на некст указывает на себя
	{
		list_element list_element_buf;
		list_element_buf.value = vertex;
		list_element_buf.head = vertex;
		list_element_buf.rank = 1;
		list.push_back(list_element_buf);
	}

	int _find_set(int vertex_u)//возвращает представительный элемент множества, содержащего u
	{
		for (int i = 0; i < list.size(); ++i)
		{
			if (list[i].value == vertex_u)
				return list[i].head;
		}
	}

	void _union(int vertex_u, int vertex_v)//объединение подмножеств
	{


		int vertex_v_head = 0;
		int vertex_u_head = 0;
		int rank_u = 0;
		int rank_v = 0;
		

		for (int i = 0; i < list.size(); ++i)
		{
			if (list[i].value == vertex_u)
			{
				vertex_u_head = list[i].head;//находим хэд веришны u
				//cout << vertex_u_head << endl;

				rank_u = list[i].rank;//находим колво элементов в подмножестве вершины u
			}

			if (list[i].value == vertex_v)
			{
				vertex_v_head = list[i].head;//находим хэд веришны v
				rank_v = list[i].rank;//находим колво элементов в подмножестве вершины v
			}
		}

		if (rank_u >= rank_v)//большее подмножество присоединяет к себе меньшее подмножество
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


	void _sort()//сортировка путей по возрастанию весов
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

