#include <iostream>
#include <string>
#include "graph.h"

int main()
{
    graph g(5); // Creates a graph with vertices A, B, C, D, E
    g.addVertex("F");
    g.addVertex("G");

    g.addEdge("A", "B");
    g.addEdge("B", "C");
    g.addEdge("C", "B");
    g.addEdge("C", "D");
    g.addEdge("D", "G");
    g.addEdge("D", "A");
    g.addEdge("A", "G");
    g.addEdge("G", "A");

    std::cout << "Graph adjacency matrix:" << std::endl;
    g.display();

    g.generateDotFile("graph.txt");

    return 0;
}