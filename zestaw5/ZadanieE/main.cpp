#include <iostream>
#include <string>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <unordered_map>
#include <set>

typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperty> graph;

std::vector<std::string> getMovements()
{
    return {
        "A->B", "A->C", "A->D",
        "B->A", "B->C", "B->D",
        "D->A", "D->B", "D->C",
        "E->A", "E->B", "E->C", "E->D"};
}

std::unordered_map<std::string, int> colorGraph(graph &G)
{
    std::unordered_map<std::string, int> colorMap;
    int color = 0;

    for (auto v : boost::make_iterator_range(boost::vertices(G)))
    {
        if (colorMap.find(boost::get(boost::vertex_name, G, v)) != colorMap.end())
        {
            continue; // Vertex already colored
        }

        colorMap[boost::get(boost::vertex_name, G, v)] = color; // Assign color to the vertex

        std::set<int> usedColors;
        usedColors.insert(color);

        // Check adjacent vertices to assign different colors
        auto [adjBegin, adjEnd] = boost::adjacent_vertices(v, G);
        for (auto it = adjBegin; it != adjEnd; ++it)
        {
            std::string adjVertexName = boost::get(boost::vertex_name, G, *it);

            if (colorMap.find(adjVertexName) != colorMap.end())
            {
                usedColors.insert(colorMap[adjVertexName]); // Collect colors of adjacent vertices
            }
        }

        for (auto it = adjBegin; it != adjEnd; ++it)
        {
            std::string adjVertexName = boost::get(boost::vertex_name, G, *it);

            if (colorMap.find(adjVertexName) == colorMap.end())
            {
                // If the adjacent vertex is not colored, assign a new color
                int newColor = 0;
                while (usedColors.find(newColor) != usedColors.end())
                {
                    newColor++;
                }
                colorMap[adjVertexName] = newColor; // Assign a new color to the adjacent vertex
            }
        }
    }

    return colorMap;
}

int main()
{
    graph G;
    std::vector<std::string> movements = getMovements();
    std::unordered_map<std::string, boost::graph_traits<graph>::vertex_descriptor> name_to_vertex;

    for (std::string &movement : movements)
    {
        boost::graph_traits<graph>::vertex_descriptor v = boost::add_vertex(VertexProperty(movement), G);
        name_to_vertex[movement] = v;
    }

    boost::add_edge(name_to_vertex["A->B"], name_to_vertex["E->A"], G);
    boost::add_edge(name_to_vertex["A->B"], name_to_vertex["B->D"], G);
    boost::add_edge(name_to_vertex["A->B"], name_to_vertex["B->C"], G);
    boost::add_edge(name_to_vertex["A->B"], name_to_vertex["D->A"], G);
    boost::add_edge(name_to_vertex["A->B"], name_to_vertex["E->B"], G);
    boost::add_edge(name_to_vertex["A->B"], name_to_vertex["D->B"], G);
    boost::add_edge(name_to_vertex["A->C"], name_to_vertex["E->A"], G);
    boost::add_edge(name_to_vertex["A->C"], name_to_vertex["B->D"], G);
    boost::add_edge(name_to_vertex["A->C"], name_to_vertex["B->C"], G);
    boost::add_edge(name_to_vertex["A->C"], name_to_vertex["E->B"], G);
    boost::add_edge(name_to_vertex["A->C"], name_to_vertex["E->C"], G);
    boost::add_edge(name_to_vertex["A->C"], name_to_vertex["D->A"], G);
    boost::add_edge(name_to_vertex["A->C"], name_to_vertex["D->B"], G);
    boost::add_edge(name_to_vertex["A->C"], name_to_vertex["D->C"], G);
    boost::add_edge(name_to_vertex["A->D"], name_to_vertex["E->A"], G);
    boost::add_edge(name_to_vertex["A->D"], name_to_vertex["E->B"], G);
    boost::add_edge(name_to_vertex["A->D"], name_to_vertex["E->C"], G);
    boost::add_edge(name_to_vertex["A->D"], name_to_vertex["E->D"], G);
    boost::add_edge(name_to_vertex["A->D"], name_to_vertex["B->D"], G);
    boost::add_edge(name_to_vertex["B->A"], name_to_vertex["D->A"], G);
    boost::add_edge(name_to_vertex["B->A"], name_to_vertex["E->A"], G);
    boost::add_edge(name_to_vertex["B->C"], name_to_vertex["E->B"], G);
    boost::add_edge(name_to_vertex["B->C"], name_to_vertex["D->A"], G);
    boost::add_edge(name_to_vertex["B->C"], name_to_vertex["D->B"], G);
    boost::add_edge(name_to_vertex["B->C"], name_to_vertex["D->C"], G);
    boost::add_edge(name_to_vertex["B->C"], name_to_vertex["E->C"], G);
    boost::add_edge(name_to_vertex["B->D"], name_to_vertex["D->A"], G);
    boost::add_edge(name_to_vertex["B->D"], name_to_vertex["E->B"], G);
    boost::add_edge(name_to_vertex["B->D"], name_to_vertex["E->C"], G);
    boost::add_edge(name_to_vertex["B->D"], name_to_vertex["E->D"], G);
    boost::add_edge(name_to_vertex["D->A"], name_to_vertex["E->C"], G);
    boost::add_edge(name_to_vertex["D->A"], name_to_vertex["E->B"], G);
    boost::add_edge(name_to_vertex["D->A"], name_to_vertex["E->A"], G);
    boost::add_edge(name_to_vertex["D->B"], name_to_vertex["E->C"], G);
    boost::add_edge(name_to_vertex["D->B"], name_to_vertex["E->B"], G);
    boost::add_edge(name_to_vertex["D->C"], name_to_vertex["E->C"], G);

    std::unordered_map<std::string, int> colorMap = colorGraph(G);
    int miniumNumberOfPhases = 0;
    std::cout << "Vertex Colors:" << std::endl;
    for (const auto &pair : colorMap)
    {
        std::cout << pair.first << " -> Color: " << pair.second << std::endl;
        if (pair.second > miniumNumberOfPhases)
        {
            miniumNumberOfPhases = pair.second;
        }
    }
    miniumNumberOfPhases++;

    std::cout << "Minimum number of phases: " << miniumNumberOfPhases << std::endl;

    return 0;
}