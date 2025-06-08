#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>

std::vector<std::vector<int>> readGraphFromFile(const std::string &filename)
{
    std::fstream file(filename);
    std::vector<std::vector<int>> graph;

    for (std::string line; std::getline(file, line);)
    {
        std::vector<int> row;
        for (const auto &c : line)
        {
            if (c == '1')
                row.push_back(1);
            else if (c == '0')
                row.push_back(0);
        }
        graph.push_back(row);
    }

    return graph;
}

bool isDirectedGraphCyclicRecurrence(std::vector<std::vector<int>> &Graph, int vertex, std::string visited[])
{
    visited[vertex] = "gray";

    for (int i = 0; i < Graph[vertex].size(); ++i)
    {
        if (visited[i] == "black")
            continue;
        if (visited[i] == "gray")
            return true;
        if (Graph[vertex][i] == 1)
        {
            if (isDirectedGraphCyclicRecurrence(Graph, i, visited))
                return true;
        }
    }

    visited[vertex] = "black";

    return false;
}

bool isCyclic(std::vector<std::vector<int>> &Graph)
{
    // Najpierw sprawdź, czy graf jest skierowany czy nieskierowany
    bool isDirected = false;
    for (size_t i = 0; i < Graph.size() && !isDirected; ++i)
    {
        for (size_t j = 0; j < Graph[i].size(); ++j)
        {
            if (Graph[i][j] != Graph[j][i])
            {
                isDirected = true;
                break;
            }
        }
    }

    if (isDirected)
    {
        std::string visited[Graph.size()];
        for (int i = 0; i < Graph.size(); ++i)
            visited[i] = "white";

        for (int i = 0; i < Graph.size(); ++i)
        {
            if (visited[i] != "white")
            {
                continue;
            }
            else if (isDirectedGraphCyclicRecurrence(Graph, i, visited))
            {
                return true;
            }
        }

        return false;
    }

    else
    {

        bool visited[Graph.size()];
        for (int i = 0; i < Graph.size(); ++i)
            visited[i] = false;

        std::stack<int> stack;

        stack.push(0);
        stack.push(-1); // -1 indicates no parent

        visited[0] = true;

        while (!stack.empty())
        {
            auto parrentVertex = stack.top();
            stack.pop();

            auto currentVertex = stack.top();
            stack.pop();

            for (int i = 0; i < Graph[currentVertex].size(); ++i)
            {
                if (Graph[currentVertex][i] == 1)
                {
                    if (!visited[i])
                    {
                        stack.push(i);
                        stack.push(currentVertex);
                        visited[i] = true;
                    }
                    else if (i != parrentVertex)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    return false;
}

int main()
{
    std::vector<std::vector<int>> g1 = readGraphFromFile("g1");
    std::vector<std::vector<int>> g2 = readGraphFromFile("g2");
    std::vector<std::vector<int>> g3 = readGraphFromFile("g3");

    bool isG1Cyclic = isCyclic(g1);
    if (isG1Cyclic)
        std::cout << "Graph g1 is cyclic." << std::endl;
    else
        std::cout << "Graph g1 is acyclic." << std::endl;

    bool isG2Cyclic = isCyclic(g2);
    if (isG2Cyclic)
        std::cout << "Graph g2 is cyclic." << std::endl;
    else
        std::cout << "Graph g2 is acyclic." << std::endl;

    bool isG3Cyclic = isCyclic(g3);
    if (isG3Cyclic)
        std::cout << "Graph g3 is cyclic." << std::endl;
    else
        std::cout << "Graph g3 is acyclic." << std::endl;

    return 0;
}