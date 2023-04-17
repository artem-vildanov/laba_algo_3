#include <iostream>
#include "Graph.h"
#include "Connected_components.h"
#include "Way.h"
#include "MST.h"

using std::cout;
using std::cin;
using std::endl;
using std::rand;
using std::vector;

Connected_components::Connected_components(MST tree)
{

	vertices_amount = tree.get_vertices_amount();
	spanning_tree = tree.get_spanning_tree();
	K_amount = set_K();

	for (int i = 0; i < (vertices_amount - K_amount); ++i)//заполнение ограниченного вектора MST
	{
		small_spanning_tree.push_back(spanning_tree[i]);
	}

	uniq_vertices_vec_init();//create array of vertices, that placed in small mst
	create_adj_matrix();//create adjacency matrix
	DFS();
	
}

void Connected_components::create_adj_matrix()
{
	Way no_way;
	no_way.weight = 0;//"null" object
	
	for (int i = 0; i < uniq_vertices.size(); ++i)
	{//попадаем на столбец матрицы

		int current_vertex_column = uniq_vertices[i];
		vector <Way> column;//столбец матрицы

		for (int j = 0; j < uniq_vertices.size(); ++j)
		{//ищем строку
			int current_vertex_string = uniq_vertices[j];
			bool way_found = false;

			for (int f = 0; f < small_spanning_tree.size(); ++f)
			{//поиск пути с этими вершинами
				
				if ((small_spanning_tree[f].vertex_u == current_vertex_column && small_spanning_tree[f].vertex_v == current_vertex_string)
				 || (small_spanning_tree[f].vertex_v == current_vertex_column && small_spanning_tree[f].vertex_u == current_vertex_string))
				{//найден путь, у которого вершина u это колонка, а вершина v это строка

					column.push_back(small_spanning_tree[f]);
					way_found = true;
					break;
				}
			}

			if (way_found == false)
				column.push_back(no_way);//если не был найден подходящий путь, то вводим пустоту

		}
		matrix_column new_column;
		new_column.way = column;
		new_column.vertex = current_vertex_column;

		Adj_matrix.push_back(new_column);//помещаем сформированный столбец в матрицу
	}
}

void Connected_components::DFS()
{

	parent = new int[vertices_amount];
	color = new int[vertices_amount];
	//0 is white, 1 is gray, 2 is black

	for (int i = 0; i < uniq_vertices.size(); ++i)
	{//initialize vertices
		parent[uniq_vertices[i]] = uniq_vertices[i];//no parent
		color[uniq_vertices[i]] = 0;//set white
	}

	for (int i = 0; i < uniq_vertices.size(); ++i)
	{//explore every white vertex in graph
		if (color[uniq_vertices[i]] == 0)//if color == white
		{
			vector <int> vertices_in_component;//одна компонента, that consists of some vertices

			DFS_Visit(uniq_vertices[i], vertices_in_component);//explore that vertex (and push that vertex in component)
			components.push_back(vertices_in_component);
		}
	}
}

void Connected_components::DFS_Visit(int vertex, vector <int> &vertices_in_component)
{
	color[vertex] = 1;//set color gray	

	for (int i = 0; i < Adj_matrix.size(); ++i)//every adj_matrix element is vertex
	{
		if (Adj_matrix[i].vertex == vertex)//find required column (required column == vertex U)
		{
			for (int j = 0; j < Adj_matrix[i].way.size(); ++j)//go for adj_matrix column elements and search there for adjacent vertices
			{//EVERY ADJACENT VERTEX 
				//the adjacent vertex can be either vertex_u or vertex_v; bec of that there 2 variants
				if  ((Adj_matrix[i].way[j].vertex_u == vertex) &&//vertex_V is adj
					(Adj_matrix[i].way[j].weight > 0) && 
					(color[Adj_matrix[i].way[j].vertex_v] == 0))
				{
					parent[Adj_matrix[i].way[j].vertex_v] = vertex;
					DFS_Visit(Adj_matrix[i].way[j].vertex_v, vertices_in_component);
				}
				//shetcoding time
				if ((Adj_matrix[i].way[j].vertex_v == vertex) &&//vertex_U is adj
					(Adj_matrix[i].way[j].weight > 0) &&
					(color[Adj_matrix[i].way[j].vertex_u] == 0))
				{
					parent[Adj_matrix[i].way[j].vertex_u] = vertex;
					DFS_Visit(Adj_matrix[i].way[j].vertex_u, vertices_in_component);
				}
			}
		}
	}

	color[vertex] = 2;//set color black
	vertices_in_component.push_back(vertex);
	//cout << vertices_in_component.back() << endl;
}

void Connected_components::uniq_vertices_vec_init()//заполнение массива уникальных вершин 
{
	for (int i = 0; i < small_spanning_tree.size(); ++i)
	{
		//для u

		int val = small_spanning_tree[i].vertex_u;
		//uniq_vertex vertex_u;
		//vertex_u.value = val;
		bool uniq_check_u = true;

		if (uniq_vertices.size() > 0)
		{
			for (int j = 0; j < uniq_vertices.size(); ++j)
			{
				if (uniq_vertices[j] == val)
				{
					uniq_check_u = false;
					break;
				}
			}
		}

		if (uniq_check_u == true)//если число является уникальлнй вершинй
		{
			uniq_vertices.push_back(val);
		}

		//для v

		val = small_spanning_tree[i].vertex_v;
		/*uniq_vertex vertex_v;
		vertex_v.value = val;*/
		bool uniq_check_v = true;

		if (uniq_vertices.size() > 0)
		{
			for (int j = 0; j < uniq_vertices.size(); ++j)
			{
				if (uniq_vertices[j] == val)
				{
					uniq_check_v = false;
					break;
				}
			}
		}

		if (uniq_check_v == true)//если число является уникальлнй вершинй
		{
			uniq_vertices.push_back(val);
		}
	}
}

void Connected_components::output_small_spanning_tree()
{
	cout << endl;
	cout << "===Small spanning tree===" << endl;
	for (int i = 0; i < small_spanning_tree.size(); ++i)
	{
		cout << "vertex u: " << small_spanning_tree[i].vertex_u << " vertex v: " << small_spanning_tree[i].vertex_v << " size: " << small_spanning_tree[i].weight << endl;
	}
}

void Connected_components::output_adj_matrix()
{
	//output vertices

	cout << endl;
	cout << "===vertices array===" << endl;

	for (int i = 0; i < uniq_vertices.size(); ++i)
		cout << " " << uniq_vertices[i] << " ";

	cout << endl;
	cout << endl;
	//output matrix

	cout << "===adj matrix===" << endl;
	for (int i = 0; i < Adj_matrix.size(); ++i)
	{
		for (int j = 0; j < Adj_matrix[i].way.size(); ++j)
		{//вывод строки (или столбца...)
			if (Adj_matrix[i].way[j].weight != 0)
				cout << " 1 ";
			else
				cout << " 0 ";
		}
		cout << endl;
	}
	cout << endl;
}

void Connected_components::output_vertices_condition()
{
	cout << endl;
	cout << "===Output of vertices, parents and colors===" << endl;

	for (int i = 0; i < uniq_vertices.size(); ++i)
	{
		cout << " vertex: " << uniq_vertices[i] << " parent: " << parent[uniq_vertices[i]] << " color: " << color[uniq_vertices[i]] << endl;
	}
	cout << endl;
}

void Connected_components::output_components()
{
	cout << endl;
	cout << "===Output of components===" << endl;

	for (int i = 0; i < components.size(); ++i)
	{
		cout << "connectivity component " << i << " : ";
		for (int j = 0; j < components[i].size(); ++j)
		{
			cout << components[i][j] << " ";
		}
		cout << endl;
		cout << "amount of elements: " << components[i].size() << endl;
	}
}

int Connected_components::set_K()
{
	int K;
	cout << "Введите количество компонентов связности: ";
	cin >> K;
	return K;
}

