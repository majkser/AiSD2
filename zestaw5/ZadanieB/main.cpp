#include <iostream>
#include <string>
#include "graph.h"

int main()
{
    graph g(5);
    g.addVertex(7);

    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 2);
    g.addEdge(3, 4);
    g.addEdge(4, 7);
    g.addEdge(4, 1);
    g.addEdge(1, 7);
    g.addEdge(7, 1);

    std::cout << "Graph adjacency matrix:" << std::endl;
    g.display();

    g.neighbors(7);
    g.generateDotFile("graph.txt");

    return 0;
}