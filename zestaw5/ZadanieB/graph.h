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
    std::unordered_map<std::string, int> verticesValues;
    int numberOfEdges;

public:
    graph(int vertices);
    ~graph(); // Changed to custom destructor
    bool adjacent(const std::string &vertex1, const std::string &vertex2);
    std::vector<std::string> neighbors(const std::string &vertex);
    void addVertex(const std::string &vertex);
    void removeVertex(const std::string &vertex);
    void addEdge(const std::string &vertex1, const std::string &vertex2);
    void removeEdge(const std::string &vertex1, const std::string &vertex2);
    int getVertexValue(const std::string &vertex);
    void setVertexValue(const std::string &vertex, int value);
    int getEdgeValue(const std::string &vertex1, const std::string &vertex2);
    void setEdgeValue(const std::string &vertex1, const std::string &vertex2, int value);
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

        // Generate a letter A, B, C, etc. for initial vertices
        char letter = 'A' + i;
        std::string vertexName(1, letter);
        verticesValues.insert({vertexName, i});
    }
}

bool graph::adjacent(const std::string &vertex1, const std::string &vertex2)
{
    if (verticesValues.contains(vertex1) && verticesValues.contains(vertex2))
    {
        return adjacencyMatrix[verticesValues.at(vertex1)][verticesValues.at(vertex2)] != 0;
    }
    return false;
}

std::vector<std::string> graph::neighbors(const std::string &vertex)
{
    if (!verticesValues.contains(vertex))
    {
        std::cout << "Vertex does not exist." << std::endl;
        return {};
    }

    int index = verticesValues.at(vertex);
    std::vector<std::string> neighbors;

    for (int i = 0; i < numberOfVertices; i++)
    {
        if (adjacencyMatrix[index][i] != 0)
        {
            // Find which vertex name corresponds to matrix index i
            for (const auto &[vtxName, idx] : verticesValues)
            {
                if (idx == i)
                {
                    neighbors.push_back(vtxName);
                    break;
                }
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

void graph::addVertex(const std::string &vertex)
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

void graph::removeVertex(const std::string &vertex)
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

    // Free old matrix memory
    for (int i = 0; i < numberOfVertices; i++)
    {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;

    adjacencyMatrix = newAdjecencyMatrix;
    numberOfVertices = newSize;
    verticesValues.erase(vertex);

    // Update indices of remaining vertices
    for (auto &[vtx, idx] : verticesValues)
    {
        if (idx > index)
        {
            idx--;
        }
    }
}

void graph::addEdge(const std::string &vertex1, const std::string &vertex2)
{
    if (verticesValues.contains(vertex1) && verticesValues.contains(vertex2))
    {
        adjacencyMatrix[verticesValues.at(vertex1)][verticesValues.at(vertex2)] = 1;
        numberOfEdges++;
    }
    else
    {
        std::cout << "One or both vertices do not exist." << std::endl;
    }
}

void graph::removeEdge(const std::string &vertex1, const std::string &vertex2)
{
    if (verticesValues.contains(vertex1) && verticesValues.contains(vertex2))
    {
        adjacencyMatrix[verticesValues.at(vertex1)][verticesValues.at(vertex2)] = 0;
        numberOfEdges--;
    }
    else
    {
        std::cout << "One or both vertices do not exist." << std::endl;
    }
}

int graph::getVertexValue(const std::string &vertex)
{
    if (verticesValues.contains(vertex))
    {
        return verticesValues.at(vertex);
    }
    return -1; // Invalid vertex
}

void graph::setVertexValue(const std::string &vertex, int value)
{
    if (verticesValues.contains(vertex))
    {
        verticesValues[vertex] = value;
    }
    else
    {
        std::cout << "Vertex does not exist." << std::endl;
    }
}

int graph::getEdgeValue(const std::string &vertex1, const std::string &vertex2)
{
    if (verticesValues.contains(vertex1) && verticesValues.contains(vertex2))
    {
        return adjacencyMatrix[verticesValues.at(vertex1)][verticesValues.at(vertex2)];
    }
    return -1; // Invalid edge
}

void graph::setEdgeValue(const std::string &vertex1, const std::string &vertex2, int value)
{
    if (verticesValues.contains(vertex1) && verticesValues.contains(vertex2))
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

    for (const auto &[vertex, index] : verticesValues)
    {
        std::vector<std::string> neighborsList = neighbors(vertex);

        for (const std::string &neighbor : neighborsList)
        {
            // Quote the vertex names to handle special characters
            dotFile << "    \"" << vertex << "\" -> \"" << neighbor << "\";" << std::endl;
        }
    }

    dotFile << "}" << std::endl;
    dotFile.close();
    std::cout << "DOT file generated: " << filename << std::endl;
}

graph::~graph()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}

#endif // graph_h