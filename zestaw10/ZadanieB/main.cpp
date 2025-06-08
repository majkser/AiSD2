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

bool isConsistent(std::vector<std::vector<int>> &Graph)
{
    // Check if the graph is directed or undirected
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
        for (size_t i = 0; i < Graph.size(); ++i)
        {
            for (size_t j = 0; j < Graph[i].size(); ++j)
            {
                if (Graph[i][j] == 1 || Graph[j][i] == 1)
                {
                    // Jeśli istnieje krawędź w którymkolwiek kierunku, dodaj w obu
                    Graph[i][j] = 1;
                    Graph[j][i] = 1;
                }
            }
        }
    }

    bool visited[Graph.size()];
    for (int i = 0; i < Graph.size(); ++i)
        visited[i] = false;

    std::stack<int> stack;
    stack.push(0);
    visited[0] = true;

    int visitedCounter = 0;

    while (!stack.empty())
    {
        auto currentVertex = stack.top();
        stack.pop();
        visitedCounter++;

        for (int i = 0; i < Graph[currentVertex].size(); ++i)
        {
            if (Graph[currentVertex][i] == 1 && !visited[i])
            {
                stack.push(i);
                visited[i] = true;
            }
        }
    }

    return visitedCounter == Graph.size();
}

int main()
{
    std::vector<std::vector<int>> h1 = readGraphFromFile("h1");
    std::vector<std::vector<int>> h2 = readGraphFromFile("h2");
    std::vector<std::vector<int>> h3 = readGraphFromFile("h3");

    std::cout << "h1 is " << (isConsistent(h1) ? "consistent" : "inconsistent") << std::endl;
    std::cout << "h2 is " << (isConsistent(h2) ? "consistent" : "inconsistent") << std::endl;
    std::cout << "h3 is " << (isConsistent(h3) ? "consistent" : "inconsistent") << std::endl;

    return 0;
}