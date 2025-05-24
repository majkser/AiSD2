#include <iostream>
#include <string>
#include "graph.h"

int main()
{
    graph graph1(5); // creates graph with vertecies from 0 to 4

    graph1.addEdge(0, 1);
    graph1.addEdge(2, 4);
    graph1.display();
    graph1.removeEdge(0, 1);
    graph1.display();
    graph1.setEdgeValue(1, 2, 5);
    std::cout << "Edge value between 1 and 2: " << graph1.getEdgeValue(1, 2) << std::endl;
    graph1.display();
    std::cout << graph1.adjacent(1, 2) << std::endl;
    std::cout << graph1.adjacent(0, 1) << std::endl;
    graph1.addVertex(6);
    graph1.addEdge(1, 6);
    graph1.display();
    std::cout << graph1.getEdgeValue(1, 6) << std::endl;
    graph1.addVertex(5);
    graph1.addEdge(5, 6);
    std::cout << graph1.getEdgeValue(5, 6) << std::endl;
    graph1.display();
    graph1.removeVertex(5);
    graph1.display();
    std::vector<int> neighbors = graph1.neighbors(6);
    std::cout << "Neighbors of vertex " << 6 << ": ";
    for (int neighbor : neighbors)
    {
        std::cout << neighbor << " ";
    }
    std::cout << std::endl;

    graph1.setVertexValue(6, 10);
    std::cout << "Value of vertex 6: " << graph1.getVertexValue(6) << std::endl;

    return 0;
}