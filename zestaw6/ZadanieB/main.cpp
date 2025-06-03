#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
// #include "../../zestaw5/ZadanieB/graph.h"
#include <boost/graph/adjacency_list.hpp>
#include <queue>
#include <unordered_set>

int countUTF8Characters(const std::string &str)
{
    int count = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        // Count the starting bytes of UTF-8 sequences
        // In UTF-8, continuation bytes start with 10xxxxxx (0x80-0xBF)
        // Starting bytes have different patterns: 0xxxxxxx, 110xxxxx, 1110xxxx, 11110xxx
        if ((str[i] & 0xC0) != 0x80)
        {
            count++;
        }
    }
    return count;
}

void letterFileFormating()
{
    std::ifstream file("slowa.txt");
    std::ofstream outputFile("slowaCzteroLiterowe.txt");
    for (std::string line; std::getline(file, line);)
    {
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        if (countUTF8Characters(line) == 4)
        {
            outputFile << line << std::endl;
        }
    }
    file.close();
    outputFile.close();
    std::cout << "Cztero-literowe slowa zapisane do pliku 'slowaCzteroLiterowe.txt'." << std::endl;
}

typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty> graph;
typedef boost::graph_traits<graph>::vertex_descriptor Vertex;

std::unordered_map<std::string, Vertex> wordToVertex;

graph buildGraph()
{
    std::ifstream file("slowaCzteroLiterowe.txt");
    std::unordered_map<std::string, std::vector<std::string>> buckets;
    graph Graph;

    for (std::string line; std::getline(file, line);)
    {
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        Vertex v = boost::add_vertex(Graph);
        boost::put(boost::vertex_name, Graph, v, line);
        wordToVertex[line] = v;

        for (size_t i = 0; i < line.length(); ++i)
        {
            std::string key = line.substr(0, i) + '_' + line.substr(i + 1);
            buckets[key].push_back(line);
        }
    }
    file.close();

    for (const auto &pair : buckets)
    {
        const std::vector<std::string> &words = pair.second;

        for (size_t i = 0; i < words.size(); ++i)
        {
            for (size_t j = i + 1; j < words.size(); ++j)
            {
                Vertex v1 = wordToVertex[words[i]];
                Vertex v2 = wordToVertex[words[j]];
                boost::add_edge(v1, v2, Graph);
            }
        }
    }

    return Graph;
}

void wordLadder()
{
    graph Graph = buildGraph();
    std::vector<Vertex> result;

    std::string startWord, endWord;

    do
    {
        std::cout << "Podaj poczatkowe slowo: ";
        std::cin >> startWord;
        std::cout << "Podaj koncowe slowo: ";
        std::cin >> endWord;
        if (countUTF8Characters(startWord) != 4 || countUTF8Characters(endWord) != 4)
            std::cout << "Oba slowa musza miec dokladnie 4 litery." << std::endl;
    } while (countUTF8Characters(startWord) != 4 || countUTF8Characters(endWord) != 4);

    int startWordIndex = wordToVertex[startWord];
    int endWordIndex = wordToVertex[endWord];
    Vertex startVertex = boost::vertex(startWordIndex, Graph);
    Vertex endVertex = boost::vertex(endWordIndex, Graph);

    std::queue<Vertex> queue;
    std::unordered_set visited = std::unordered_set<Vertex>();
    std::unordered_map<Vertex, Vertex> parentMap;

    queue.push(startVertex);
    visited.insert(startVertex);

    bool pathFound = false;

    while (!queue.empty() && !pathFound)
    {
        Vertex currentVertex = queue.front();
        queue.pop();

        if (currentVertex == endVertex)
        {
            pathFound = true;
            break;
        }

        auto [neighborsBegin, neighborsEnd] = boost::adjacent_vertices(currentVertex, Graph);
        for (auto it = neighborsBegin; it != neighborsEnd; ++it)
        {
            Vertex neighbor = *it;
            if (visited.find(neighbor) == visited.end())
            {
                visited.insert(neighbor);
                queue.push(neighbor);
                // std::cout << "Odwiedzono: " << boost::get(boost::vertex_name, Graph, neighbor) << std::endl;
                parentMap[neighbor] = currentVertex;
            }
        }
    }

    if (pathFound)
    {
        std::vector<Vertex> path;
        Vertex current = endVertex;

        while (current != startVertex)
        {
            path.push_back(current);
            current = parentMap[current];
        }
        path.push_back(startVertex);

        // Print the path in correct order
        std::cout << "Word ladder: ";
        for (auto it = path.rbegin(); it != path.rend(); ++it)
        {
            std::cout << boost::get(boost::vertex_name, Graph, *it);
            if (it != path.rend() - 1)
            {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Nie znaleziono sciezki miedzy " << startWord << " a " << endWord << std::endl;
    }
}

int main()
{
    // letterFileFormating();
    // buildGraph();
    wordLadder();

    return 0;
}