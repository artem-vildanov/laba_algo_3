#pragma once

using std::rand;

class Way
{
public:
	//������� u
	int vertex_u;

	//������� v (������� �� ��������� � u)
	int vertex_v;

	//��� ����
	int weight;

	Way()
	{
		weight = (rand() % 100) + 1;
	}

};