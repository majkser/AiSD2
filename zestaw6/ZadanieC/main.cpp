#include <iostream>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_map>

typedef boost::property<boost::vertex_name_t, std::string> VertexProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperty> graph;

void dfs(graph &g, graph::vertex_descriptor v, std::vector<bool> &visited, std::vector<graph::vertex_descriptor> &sortedVertices, int &counter, std::unordered_map<graph::vertex_descriptor, int> &vertexDiscoveryTime, std::unordered_map<graph::vertex_descriptor, int> &vertexFinishTime)
{
    visited[v] = true;
    vertexDiscoveryTime[v] = counter;
    sortedVertices.push_back(v);
    counter++;

    // Get all adjacent vertices
    auto [adjBegin, adjEnd] = boost::adjacent_vertices(v, g);
    for (auto it = adjBegin; it != adjEnd; it++)
    {
        if (!visited[*it])
        {
            dfs(g, *it, visited, sortedVertices, counter, vertexDiscoveryTime, vertexFinishTime);
        }
    }

    vertexFinishTime[v] = counter;
    counter++;
}

void getOrder(graph &g)
{
    std::vector<graph::vertex_descriptor> sortedVertices;
    std::vector<bool> visited(boost::num_vertices(g), false);
    std::unordered_map<graph::vertex_descriptor, int> vertexDiscoveryTime;
    std::unordered_map<graph::vertex_descriptor, int> vertexFinishTime;
    int counter = 0;

    for (size_t i = 0; i < boost::num_vertices(g); ++i)
    {
        graph::vertex_descriptor v = boost::vertex(i, g);
        if (!visited[v])
        {
            dfs(g, v, visited, sortedVertices, counter, vertexDiscoveryTime, vertexFinishTime);
        }
    }

    std::cout << "Vertex Finish Times:" << std::endl;
    for (const auto &pair : vertexFinishTime)
    {
        std::cout << boost::get(boost::vertex_name, g, pair.first) << ", Finish Time: " << pair.second << std::endl;
    }
}

int main()
{
    graph g;
    std::ofstream outputFile("pancakes_recipe.dot");

    auto v1 = boost::add_vertex(VertexProperty("1 egg"), g);
    auto v2 = boost::add_vertex(VertexProperty("1 tablespoon of oil"), g);
    auto v3 = boost::add_vertex(VertexProperty("3/4 cup flour"), g);
    auto v4 = boost::add_vertex(VertexProperty("1 cup of panckake mix"), g);
    auto v5 = boost::add_vertex(VertexProperty("heat griddle"), g);
    auto v6 = boost::add_vertex(VertexProperty("mix ingredients"), g);
    auto v7 = boost::add_vertex(VertexProperty("pour 1/4 of the mix"), g);
    auto v8 = boost::add_vertex(VertexProperty("turn when golden brown"), g);
    auto v9 = boost::add_vertex(VertexProperty("heat the syroup"), g);
    auto v10 = boost::add_vertex(VertexProperty("take off when golden brwon from both sides"), g);
    auto v11 = boost::add_vertex(VertexProperty("eat with syroup"), g);

    boost::add_edge(v1, v6, g);
    boost::add_edge(v2, v6, g);
    boost::add_edge(v3, v6, g);
    boost::add_edge(v4, v6, g);

    boost::add_edge(v6, v9, g);
    boost::add_edge(v9, v11, g);

    boost::add_edge(v5, v7, g);
    boost::add_edge(v6, v7, g);
    boost::add_edge(v7, v8, g);
    boost::add_edge(v8, v10, g);
    boost::add_edge(v10, v11, g);

    boost::write_graphviz(outputFile, g, boost::make_label_writer(boost::get(boost::vertex_name, g)));

    outputFile.close();

    std::cout << "Graph written to pancakes_recipe.dot" << std::endl;

    getOrder(g);

    return 0;
}