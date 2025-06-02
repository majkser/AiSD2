#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include "../../zestaw5/ZadanieB/graph.h"

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

graph buildGraph()
{
    std::ifstream file("slowaCzteroLiterowe.txt");
    std::unordered_map<std::string, std::vector<std::string>> buckets;
    graph Graph(0);

    for (std::string line; std::getline(file, line);)
    {
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        for (size_t i = 0; i < line.length(); ++i)
        {
            std::string key = line;
            key.erase(i, 1); // Remove the character at position i
            buckets[key].push_back(line);
        }
    }
    file.close();

    for (const auto &pair : buckets)
    {
        const std::string &key = pair.first;
        const std::vector<std::string> &words = pair.second;

        for (const auto &word : words)
        {
            Graph.addVertex(word);
        }

        for (size_t i = 0; i < words.size(); ++i)
        {
            for (size_t j = i + 1; j < words.size(); ++j)
            {
                Graph.addEdge(words[i], words[j]);
            }
        }
    }

    return Graph;
}

int main()
{
    // letterFileFormating();
    buildGraph();

    return 0;
}