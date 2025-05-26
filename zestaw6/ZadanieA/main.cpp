#include <iostream>
#include <string>
#include "../../zestaw5/ZadanieB/graph.h"
#include <unordered_set>
#include <vector>

std::vector<std::string> knigtsTour(std::string start, graph &g)
{
    int totalSquares = 64;
    std::vector<std::string> path;
    std::unordered_set<std::string> visited;

    std::string current = start;
    path.push_back(current);
    visited.insert(current);

    while (visited.size() < totalSquares)
    {
        std::vector<std::string> neighbors = g.neighbors(current);
        std::string next = "";

        int fewestMoves = INT_MAX;
        for (const auto &neighbor : neighbors)
        {
            if (!visited.contains(neighbor))
            {
                std::vector<std::string> neighborMoves = g.neighbors(neighbor);
                int availableMoves = 0;
                for (const auto &move : neighborMoves)
                {
                    if (!visited.contains(move))
                        availableMoves++;
                }

                if (availableMoves < fewestMoves)
                {
                    fewestMoves = availableMoves;
                    next = neighbor;
                }
            }
        }

        current = next;
        path.push_back(current);
        visited.insert(current);
    }

    return path;
}

int main()
{
    graph chessGraph(0);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            std::string vertex = std::string(1, 'A' + i) + std::to_string(j + 1);
            chessGraph.addVertex(vertex);
        }
    }

    const std::pair<int, int> move_offsets[] = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char LetterValue = 'A' + i;

            for (const auto &offset : move_offsets)
            {
                if (LetterValue + offset.first >= 'A' && LetterValue + offset.first <= 'H' &&
                    j + 1 + offset.second >= 1 && j + 1 + offset.second <= 8)
                {
                    std::string from = std::string(1, LetterValue) + std::to_string(j + 1);
                    std::string to = std::string(1, LetterValue + offset.first) + std::to_string(j + 1 + offset.second);

                    chessGraph.addEdge(from, to);
                }
            }
        }
    }

    std::vector<std::string> result = knigtsTour("H2", chessGraph);
    std::cout << "Knight's Tour Path:" << std::endl;

    int count = 1;
    std::unordered_set<std::string> duplicateCheckSet = {};
    for (const auto &vertex : result)
    {
        if (duplicateCheckSet.contains(vertex))
        {
            std::cout << "Duplicate vertex found: " << vertex << std::endl;
            continue;
        }
        duplicateCheckSet.insert(vertex);
        std::cout << count << ": " << vertex << std::endl;
        count++;
    }
    std::cout << std::endl;

    return 0;
}