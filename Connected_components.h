#pragma once
#include <iostream>
#include <vector>
#include "Way.h"
#include "list_element.h"
#include "MST.h"

using std::vector;

class Connected_components
{
	int vertices_amount;//���������� ������ ��������� �����
	int K_amount;//���������� ���������

	vector <Way> spanning_tree;//������, ���������� ����������� �������� ������ (from MST)
	vector <Way> small_spanning_tree;//������, ���������� ������������ MST (in other words is a new graph)

	//struct uniq_vertex 
	//{
	//	int value;//vertex val
	//	int color;//for dfs; white = 0 (not discovered); gray = 1 (discovered and in stack); black = 2 (is a part of a component);
	//	int parent;//???parent????
	//};

	struct matrix_column
	{
		vector <Way> way;
		int vertex;
	};

	vector <matrix_column> Adj_matrix;//�������	
	vector <int> uniq_vertices;//������ ���������� ������ �� small_mst (is neccecery for creatin matrix and for DFS algo)
	vector <vector <int>> components;//����� ����������� ���������
	
	/*vector <int> parent;
	vector <int> color;*/

	int* parent;//array of vertices parents
	int* color;//array of vertices colors (current conditions)

	int* size;//sizes of vertices (indeces) in a tree; neccecery for centroid algo

public:

	Connected_components(MST tree);
	void output_small_spanning_tree();//mst console output
	void output_adj_matrix();//mst vertices and adj matrix concole output
	void output_vertices_condition();//values, colors, parents
	void output_components();

private:

	void create_adj_matrix();//�������� ������� ��������� �����, ���������� �� (N - K) �����, ��������������� �� �����������
	void DFS();//����������� ����������� ��������� ��������� �������� ������ � �������
	void DFS_Visit(int vertex, vector <int> &vertices_in_component);//��������� ������� ��� DFS; explore ����� ������� �����	
	void uniq_vertices_vec_init();//���������� ������� ������ �� small_mst

	int set_K();//������ ���������� ���������
};