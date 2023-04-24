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
	int vertices_amount;//���������� ������ ��������� �����
	int K_amount;//���������� ���������

	vector <Way> spanning_tree;//������, ���������� ����������� �������� ������ (from MST)
	vector <Way> small_spanning_tree;//������, ���������� ������������ MST (in other words is a new graph)
	vector <Coordinate_vertex> coordinates;//������ ��������� ������ �����

	//struct uniq_vertex 
	//{
	//	int value;//vertex val
	//	int color;//for dfs; white = 0 (not discovered); gray = 1 (discovered and in stack); black = 2 (is a part of a component);
	//	int parent;//???parent????
	//};

	struct matrix_column//������� ������� ��� ����� ������� � ������ ������� � ��� ������ 
	{
		vector <Way> way;
		int vertex;
	};

	struct component//� ������ ���������� ���� �� ����� ������ � ���������� ��������� ���� ����������
	{
		vector <int> vertices_in_component;
		
		double X_centrtoid = -1;
		double Y_centrtoid = -1;

		double X_max = -1;
		double Y_max = -1;

		double Y_min = -1;
		double X_min = -1;
	};

	vector <matrix_column> Adj_matrix;//�������	
	vector <int> uniq_vertices;//������ ���������� ������ �� small_mst (is neccecery for creatin matrix and for DFS algo)
	vector <component> components;//����� ����������� ���������
	
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

	void create_adj_matrix();//�������� ������� ��������� �����, ���������� �� (N - K) �����, ��������������� �� �����������
	void DFS();//����������� ����������� ��������� ��������� �������� ������ � �������
	void DFS_Visit(int vertex, vector <int> &vertices_in_component);//��������� ������� ��� DFS; explore ����� ������� �����	
	void uniq_vertices_vec_init();//���������� ������� ������ �� small_mst

	void find_cendroid();
	void find_min_max_coords();

	int set_K();//������ ���������� ���������
};