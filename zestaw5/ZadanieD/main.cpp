#include <iostream>
#include "../ZadanieB/graph.h"

int main()
{
    graph G(5); // Creates a graph with vertices A, B, C, D, E

    G.addEdge("A", "B");
    G.addEdge("A", "C");
    G.addEdge("A", "D");

    G.addEdge("B", "A");
    G.addEdge("B", "C");
    G.addEdge("B", "D");

    G.addEdge("D", "A");
    G.addEdge("D", "B");
    G.addEdge("D", "C");

    G.addEdge("E", "A");
    G.addEdge("E", "B");
    G.addEdge("E", "C");
    G.addEdge("E", "D");

    G.generateDotFile("graph.txt");

    return 0;
}
