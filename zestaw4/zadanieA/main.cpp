#include <iostream>
#include <string>
#include "graph.h"

int main()
{
    // Create a graph with 5 initial vertices (A, B, C, D, E)
    graph graph1(5);

    std::cout << "Initial graph (5 vertices):" << std::endl;
    graph1.display();

    // Test adding edges
    std::cout << "\nAdding edges: A-B and C-E" << std::endl;
    graph1.addEdge("A", "B");
    graph1.addEdge("C", "E");
    graph1.display();

    // Test removing edges
    std::cout << "\nRemoving edge: A-B" << std::endl;
    graph1.removeEdge("A", "B");
    graph1.display();

    // Test setting edge values
    std::cout << "\nSetting edge value: B-C to 5" << std::endl;
    graph1.setEdgeValue("B", "C", 5);
    std::cout << "Edge value between B and C: " << graph1.getEdgeValue("B", "C") << std::endl;
    graph1.display();

    // Test adjacency
    std::cout << "\nTesting adjacency:" << std::endl;
    std::cout << "B adjacent to C: " << graph1.adjacent("B", "C") << std::endl;
    std::cout << "A adjacent to B: " << graph1.adjacent("A", "B") << std::endl;

    // Test adding a vertex
    std::cout << "\nAdding new vertex: F" << std::endl;
    graph1.addVertex("F");
    graph1.addEdge("B", "F");
    graph1.display();
    std::cout << "Edge value between B and F: " << graph1.getEdgeValue("B", "F") << std::endl;

    // Test adding another vertex
    std::cout << "\nAdding another vertex: G" << std::endl;
    graph1.addVertex("G");
    graph1.addEdge("G", "F");
    std::cout << "Edge value between G and F: " << graph1.getEdgeValue("G", "F") << std::endl;
    graph1.display();

    // Test removing a vertex
    std::cout << "\nRemoving vertex: G" << std::endl;
    graph1.removeVertex("G");
    graph1.display();

    // Test neighbors
    std::cout << "\nFinding neighbors of vertex B:" << std::endl;
    std::vector<std::string> neighbors = graph1.neighbors("B");
    std::cout << "Neighbors of vertex B: ";
    for (const std::string &neighbor : neighbors)
    {
        std::cout << neighbor << " ";
    }
    std::cout << std::endl;

    // Test vertex values
    std::cout << "\nSetting vertex value: F to 10" << std::endl;
    graph1.setVertexValue("F", 10);
    std::cout << "Value of vertex F: " << graph1.getVertexValue("F") << std::endl;

    return 0;
}