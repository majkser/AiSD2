#ifndef graph_h
#define graph_h

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

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
    std::vector<int> neighbors(int vertex);
    void addVertex(int vertex);
    void removeVertex(int vertex);
    void addEdge(int vertex1, int vertex2);
    void removeEdge(int vertex1, int vertex2);
    int getVertexValue(int vertex);
    void setVertexValue(int vertex, int value);
    int getEdgeValue(int vertex1, int vertex2);
    void setEdgeValue(int vertex1, int vertex2, int value);
    void display();
    void generateDotFile(const std::string &filename);
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

std::vector<int> graph::neighbors(int vertex)
{
    if (vertex < 0 || !verticesValues.contains(vertex))
    {
        std::cout << "Vertex does not exist." << std::endl;
        return {};
    }

    int index = verticesValues.at(vertex);
    std::vector<int> neighbors;

    for (int i = 0; i < numberOfVertices; i++)
    {
        if (adjacencyMatrix[index][i] != 0)
        {
            std::unordered_map<int, int>::iterator it = verticesValues.begin();
            while (it != verticesValues.end())
            {
                if (it->second == i)
                {
                    neighbors.push_back(it->first);
                    break;
                }
                it++;
            }
        }
    }

    if (neighbors.empty())
    {
        std::cout << "No neighbors found for vertex " << vertex << "." << std::endl;
        return {};
    }

    return neighbors;
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

    for (int i = 0; i < newSize; i++)
    {
        newAdjecencyMatrix[i] = new int[newSize];

        for (int j = 0; j < newSize; j++)
        {
            if (i < index && j < index)
            {
                newAdjecencyMatrix[i][j] = adjacencyMatrix[i][j];
            }
            else if (i < index && j >= index)
            {
                newAdjecencyMatrix[i][j] = adjacencyMatrix[i][j + 1];
            }
            else if (i >= index && j < index)
            {
                newAdjecencyMatrix[i][j] = adjacencyMatrix[i + 1][j];
            }
            else
            {
                newAdjecencyMatrix[i][j] = adjacencyMatrix[i + 1][j + 1];
            }
        }
    }
    adjacencyMatrix = newAdjecencyMatrix;
    numberOfVertices = newSize;
    verticesValues.erase(vertex);
}

void graph::addEdge(int vertex1, int vertex2)
{
    if (vertex1 >= 0 && vertex2 >= 0)
    {
        adjacencyMatrix[verticesValues.at(vertex1)][verticesValues.at(vertex2)] = 1;
        numberOfEdges++;
    }
}

void graph::removeEdge(int vertex1, int vertex2)
{
    if (vertex1 >= 0 && vertex2 >= 0 && vertex1 < numberOfVertices && vertex2 < numberOfVertices)
    {
        adjacencyMatrix[verticesValues.at(vertex1)][verticesValues.at(vertex2)] = 0;
        numberOfEdges--;
    }
}

int graph::getVertexValue(int vertex)
{
    if (vertex >= 0 && verticesValues.contains(vertex))
    {
        return verticesValues.at(vertex);
    }
    return -1; // Invalid vertex
}

void graph::setVertexValue(int vertex, int value)
{
    if (vertex >= 0 && verticesValues.contains(vertex))
    {
        verticesValues[vertex] = value;
    }
    else
    {
        std::cout << "Vertex does not exist." << std::endl;
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

void graph::generateDotFile(const std::string &filename)
{
    std::ofstream dotFile(filename);

    if (numberOfVertices == 0)
    {
        std::cout << "Graph is empty." << std::endl;
        return;
    }

    dotFile << "digraph G {" << std::endl;

    std::unordered_map<int, int>::iterator it = verticesValues.begin();
    while (it != verticesValues.end())
    {
        int vertex = it->first;
        std::vector<int> neighborsList = neighbors(vertex);

        for (int neighbor : neighborsList)
        {
            dotFile << "    " << vertex << " -> " << neighbor << ";" << std::endl;
        }

        it++;
    }
    dotFile << "}" << std::endl;
    dotFile.close();
    std::cout << "DOT file generated: " << filename << std::endl;
}

#endif // graph_h