#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <iomanip>
#include <algorithm>

int main()
{
    // Read the data file
    std::ifstream file("czasy");

    // Extract all unique cities and build the graph
    std::unordered_map<std::string, int> cityToIndex;
    std::vector<std::string> cities;
    std::vector<std::vector<int>> dist; // renamed from graph to dist for clarity
    std::vector<std::vector<int>> prev; // to store predecessor vertices

    std::string from, to;
    int time;

    while (file >> from >> to >> time)
    {
        // Add cities to the mapping if they don't exist
        for (const auto &city : {from, to})
        {
            if (cityToIndex.find(city) == cityToIndex.end())
            {
                cityToIndex[city] = cities.size();
                cities.push_back(city);
                // Expand the dist matrix with a new row and column
                for (auto &row : dist)
                {
                    row.push_back(std::numeric_limits<int>::max() / 2); // Avoid overflow
                }
                dist.push_back(std::vector<int>(cities.size(), std::numeric_limits<int>::max() / 2));

                // Also expand the prev matrix
                for (auto &row : prev)
                {
                    row.push_back(-1); // -1 indicates no path exists
                }
                prev.push_back(std::vector<int>(cities.size(), -1));

                // Distance to self is 0
                dist[cityToIndex[city]][cityToIndex[city]] = 0;
                prev[cityToIndex[city]][cityToIndex[city]] = cityToIndex[city];
            }
        }

        // Add the direct connection
        int fromIdx = cityToIndex[from];
        int toIdx = cityToIndex[to];
        dist[fromIdx][toIdx] = time;
        dist[toIdx][fromIdx] = time; // Assuming bidirectional roads

        // Set the predecessor for direct connections
        prev[fromIdx][toIdx] = fromIdx;
        prev[toIdx][fromIdx] = toIdx;
    }

    // Apply Floyd-Warshall algorithm
    for (int k = 0; k < cities.size(); ++k)
    {
        for (int i = 0; i < cities.size(); ++i)
        {
            for (int j = 0; j < cities.size(); ++j)
            {
                if (dist[i][k] != std::numeric_limits<int>::max() / 2 &&
                    dist[k][j] != std::numeric_limits<int>::max() / 2)
                {
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        prev[i][j] = prev[k][j]; // Update predecessor
                    }
                }
            }
        }
    }

    // Sort cities alphabetically for consistent output
    std::vector<int> sortedIndices(cities.size());
    for (int i = 0; i < cities.size(); ++i)
    {
        sortedIndices[i] = i;
    }
    std::sort(sortedIndices.begin(), sortedIndices.end(), [&](int a, int b)
              { return cities[a] < cities[b]; });

    // Output results to both console and file
    std::ofstream outFile("najkrotsze_czasy.txt");

    // Find column widths
    const int cityColWidth = 20;
    std::vector<int> colWidths(cities.size(), 6); // Minimum width of 6 for travel times

    // Write header
    std::cout << std::setw(cityColWidth) << "FROM/TO";
    outFile << std::setw(cityColWidth) << "FROM/TO";
    for (int j : sortedIndices)
    {
        std::cout << std::setw(colWidths[j]) << cities[j];
        outFile << std::setw(colWidths[j]) << cities[j];
    }
    std::cout << std::endl;
    outFile << std::endl;

    // Write data rows
    for (int i : sortedIndices)
    {
        std::cout << std::setw(cityColWidth) << cities[i];
        outFile << std::setw(cityColWidth) << cities[i];
        for (int j : sortedIndices)
        {
            std::cout << std::setw(colWidths[j]) << dist[i][j];
            outFile << std::setw(colWidths[j]) << dist[i][j];
        }
        std::cout << std::endl;
        outFile << std::endl;
    }

    outFile.close();
    std::cout << "\nResults also saved to 'najkrotsze_czasy.txt'" << std::endl;

    return 0;
}