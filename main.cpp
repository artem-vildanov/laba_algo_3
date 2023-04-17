
#include <iostream>
#include <time.h>
#include "Graph.h"
#include "Way.h"
#include "MST.h"
#include "Connected_components.h"

using std::cout;
using std::endl;



int main()
{
    setlocale(LC_ALL, "RUS");
    //srand(time(NULL));

    int vertices_amount = 19;

    Graph my_graph(vertices_amount);
    my_graph.output_ways();

    MST MST(my_graph);
    MST.output_spanning_tree();
    MST.output_list();

    Connected_components component(MST);
    component.output_small_spanning_tree();
    component.output_adj_matrix();
    component.output_vertices_condition();
    component.output_components();
}

