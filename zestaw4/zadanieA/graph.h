#ifndef graph_h
#define graph_h

#include <iostream>
#include <string>

class graph
{
private:
    int **adjacencyMatrix;
    int numberOfVertices;
    int numberOfEdges;

public:
    graph(int vertices);
    ~graph();
    void adjacent(int vertex1, int vertex2);
    void neighbors(int vertex);
    void addVertex(int vertex);
    void removeVertex(int vertex);
    void addEdge(int vertex1, int vertex2);
    void removeEdge(int vertex1, int vertex2);
    int getVertexValue(int vertex);
    void setVertexValue(int vertex, int value);
    int getEdgeValue(int vertex1, int vertex2);
    void setEdgeValue(int vertex1, int vertex2, int value);
    void display();
};

graph::graph(int vertices)
{
    numberOfVertices = vertices;
    numberOfEdges = 0;

    adjacencyMatrix = new int *[vertices];

    for (int i = 0; i < vertices; i++)
    {
        adjacencyMatrix[i] = new int[vertices];

        for (int j = 0; j < vertices; j++)
        {
            adjacencyMatrix[i][j] = 0;
        }
    }
}

graph::~graph() {}

void graph::addEdge(int vertex1, int vertex2)
{
    if (vertex1 >= 0 && vertex2 >= 0 && vertex1 < numberOfVertices && vertex2 < numberOfVertices)
    {
        adjacencyMatrix[vertex1][vertex2] = 1;
        adjacencyMatrix[vertex2][vertex1] = 1;
        numberOfEdges++;
    }
}

void graph::removeEdge(int vertex1, int vertex2)
{
    if (vertex1 >= 0 && vertex2 >= 0 && vertex1 < numberOfVertices && vertex2 < numberOfVertices)
    {
        adjacencyMatrix[vertex1][vertex2] = 0;
        adjacencyMatrix[vertex2][vertex1] = 0;
        numberOfEdges--;
    }
}

int graph::getEdgeValue(int vertex1, int vertex2)
{
    if (vertex1 >= 0 && vertex2 >= 0 && vertex1 < numberOfVertices && vertex2 < numberOfVertices)
    {
        return adjacencyMatrix[vertex1][vertex2];
    }
    return -1; // Invalid edge
}

void graph::setEdgeValue(int vertex1, int vertex2, int value)
{
    if (vertex1 >= 0 && vertex2 >= 0 && vertex1 < numberOfVertices && vertex2 < numberOfVertices)
    {
        adjacencyMatrix[vertex1][vertex2] = value;
        adjacencyMatrix[vertex2][vertex1] = value;
    }
}

void graph::display()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        for (int j = 0; j < numberOfVertices; j++)
        {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

#endif // graph_h