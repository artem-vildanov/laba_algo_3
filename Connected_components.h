#pragma once
#include <iostream>
#include <vector>
#include "Way.h"
#include "list_element.h"
#include "MST.h"
#include "Coordinates.h"

using std::vector;

class Connected_components
{
	int vertices_amount;//количество вершин исходного графа
	int K_amount;//количество кластеров

	vector <Way> spanning_tree;//вектор, содержащий минимальное остовное дерево (from MST)
	vector <Way> small_spanning_tree;//вектор, содержащий ограниченное MST (in other words is a new graph)
	vector <Coordinate_vertex> coordinates;//вектор координат вершин графа

	//struct uniq_vertex 
	//{
	//	int value;//vertex val
	//	int color;//for dfs; white = 0 (not discovered); gray = 1 (discovered and in stack); black = 2 (is a part of a component);
	//	int parent;//???parent????
	//};

	struct matrix_column//столбец матрицы это номер вершины и вектор смежных к ней вершин 
	{
		vector <Way> way;
		int vertex;
	};

	struct component//у каждой компоненты есть ее набор вершин и координата центроида этой компоненты
	{
		vector <int> vertices_in_component;
		
		double X_centrtoid = -1;
		double Y_centrtoid = -1;

		double X_max = -1;
		double Y_max = -1;

		double Y_min = -1;
		double X_min = -1;
	};

	vector <matrix_column> Adj_matrix;//матрица	
	vector <int> uniq_vertices;//вектор уникальных вершин из small_mst (is neccecery for creatin matrix and for DFS algo)
	vector <component> components;//набор компонентов связности
	
	/*vector <int> parent;
	vector <int> color;*/

	int* parent;//array of vertices parents
	int* color;//array of vertices colors (current conditions)
	


public:

	Connected_components(MST tree, Graph graph);
	void output_small_spanning_tree();//mst console output
	void output_adj_matrix();//mst vertices and adj matrix concole output
	void output_vertices_condition();//values, colors, parents
	void output_components();

private:

	void create_adj_matrix();//создание матрицы смежности графа, состоящего из (N - K) путей, отсортированных по возрастанию
	void DFS();//определение компонентов связности используя алгоритм поиска в глубину
	void DFS_Visit(int vertex, vector <int> &vertices_in_component);//служебная функция для DFS; explore белой вершины графа	
	void uniq_vertices_vec_init();//заполнение массива вершин из small_mst

	void find_cendroid();
	void find_min_max_coords();

	int set_K();//сеттер количества кластеров
};