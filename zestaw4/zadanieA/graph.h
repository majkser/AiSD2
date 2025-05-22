#ifndef graph_h
#define graph_h

#include <iostream>
#include <string>
#include <unordered_map>

class graph
{
private:
    int **adjacencyMatrix;
    int numberOfVertices;
    std::unordered_map<int, int> verticesValues;
    int numberOfEdges;

public:
    graph(int vertices);
    ~graph() = default;
    bool adjacent(int vertex1, int vertex2);
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
        verticesValues.insert({i, i});
    }
}

bool graph::adjacent(int vertex1, int vertex2)
{
    if (vertex1 >= 0 && vertex2 >= 0)
    {
        return adjacencyMatrix[verticesValues.at(vertex1)][verticesValues.at(vertex2)] != 0;
    }
    return false;
}

void graph::addVertex(int vertex)
{
    if (verticesValues.contains(vertex))
    {
        std::cout << "Vertex already exists." << std::endl;
        return;
    }

    int newSize = numberOfVertices + 1;
    int **newAdjacencyMatrix = new int *[newSize];

    for (int i = 0; i < newSize; i++)
    {
        newAdjacencyMatrix[i] = new int[newSize];

        for (int j = 0; j < newSize; j++)
        {
            if (i < numberOfVertices && j < numberOfVertices)
            {
                newAdjacencyMatrix[i][j] = adjacencyMatrix[i][j];
            }
            else
            {
                newAdjacencyMatrix[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < numberOfVertices; i++)
    {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;

    adjacencyMatrix = newAdjacencyMatrix;
    numberOfVertices = newSize;
    verticesValues.insert({vertex, newSize - 1});
}

void graph::removeVertex(int vertex)
{
    if (!verticesValues.contains(vertex))
    {
        std::cout << "Vertex does not exist." << std::endl;
        return;
    }

    int index = verticesValues.at(vertex);
    int newSize = numberOfVertices - 1;
    int **newAdjecencyMatrix = new int *[newSize];
    // todo: finish this method and add the rest of the methods
}

void graph::addEdge(int vertex1, int vertex2)
{
    if (vertex1 >= 0 && vertex2 >= 0)
    {
        adjacencyMatrix[verticesValues.at(vertex1)][verticesValues.at(vertex2)] = 1;
        adjacencyMatrix[verticesValues.at(vertex2)][verticesValues.at(vertex1)] = 1;
        numberOfEdges++;
    }
}

void graph::removeEdge(int vertex1, int vertex2)
{
    if (vertex1 >= 0 && vertex2 >= 0 && vertex1 < numberOfVertices && vertex2 < numberOfVertices)
    {
        adjacencyMatrix[verticesValues.at(vertex1)][verticesValues.at(vertex2)] = 0;
        adjacencyMatrix[verticesValues.at(vertex2)][verticesValues.at(vertex1)] = 0;
        numberOfEdges--;
    }
}

int graph::getEdgeValue(int vertex1, int vertex2)
{
    if (vertex1 >= 0 && vertex2 >= 0)
    {
        return adjacencyMatrix[verticesValues.at(vertex1)][verticesValues.at(vertex2)];
    }
    return -1; // Invalid edge
}

void graph::setEdgeValue(int vertex1, int vertex2, int value)
{
    if (vertex1 >= 0 && vertex2 >= 0 && vertex1 < numberOfVertices && vertex2 < numberOfVertices)
    {
        adjacencyMatrix[verticesValues.at(vertex1)][verticesValues.at(vertex2)] = value;
        adjacencyMatrix[verticesValues.at(vertex2)][verticesValues.at(vertex1)] = value;
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