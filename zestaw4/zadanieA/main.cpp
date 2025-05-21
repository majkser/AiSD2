#include <iostream>
#include <string>
#include "graph.h"

int main()
{
    graph graph1(5);

    graph1.addEdge(0, 1);
    graph1.addEdge(2, 4);
    graph1.display();
    graph1.removeEdge(0, 1);
    graph1.display();
    graph1.setEdgeValue(1, 2, 5);
    std::cout << "Edge value between 1 and 2: " << graph1.getEdgeValue(1, 2) << std::endl;
    graph1.display();

    return 0;
}