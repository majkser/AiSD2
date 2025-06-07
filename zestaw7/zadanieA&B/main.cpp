#include <iostream>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/range/iterator_range.hpp>
#include <fstream>
#include <unordered_map>
#include "priorityQueue.h"

typedef boost::property<boost::vertex_name_t, char> VertexProperty;
typedef boost::property<boost::edge_weight_t, int> EdgeProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty> graph;

std::unordered_map<graph::vertex_descriptor, int> Dijkstra(graph &g, auto startingVertex)
{
    std::unordered_map<graph::vertex_descriptor, int> shortestPaths;
    std::unordered_map<graph::vertex_descriptor, bool> visited;

    for (auto v : boost::make_iterator_range(boost::vertices(g)))
    {
        shortestPaths[v] = std::numeric_limits<int>::max(); // Initialize all distances to infinity
        visited[v] = false;
    }

    shortestPaths[startingVertex] = 0;

    priorityQueue pq;
    pq.add(startingVertex, 0);

    while (!pq.isEmpty())
    {
        auto popedElement = pq.deleteMin();
        auto currentVertex = popedElement.first;
        auto currentDistance = popedElement.second;

        visited[currentVertex] = true;

        auto [adjBegin, adjEnd] = boost::adjacent_vertices(currentVertex, g);
        for (auto it = adjBegin; it != adjEnd; it++)
        {
            if (visited[*it])
            {
                continue;
            }

            int distace = currentDistance + boost::get(boost::edge_weight, g, boost::edge(currentVertex, *it, g).first);

            if (distace < shortestPaths[*it])
            {
                shortestPaths[*it] = distace;
                pq.add(*it, distace);
            }
        }
    }

    return shortestPaths;
}

int main()
{
    graph g;

    auto vertexA = boost::add_vertex(VertexProperty('A'), g);
    auto vertexB = boost::add_vertex(VertexProperty('B'), g);
    auto vertexC = boost::add_vertex(VertexProperty('C'), g);
    auto vertexD = boost::add_vertex(VertexProperty('D'), g);
    auto vertexE = boost::add_vertex(VertexProperty('E'), g);
    auto vertexF = boost::add_vertex(VertexProperty('F'), g);
    auto vertexG = boost::add_vertex(VertexProperty('G'), g);
    auto vertexH = boost::add_vertex(VertexProperty('H'), g);
    auto vertexI = boost::add_vertex(VertexProperty('I'), g);
    auto vertexJ = boost::add_vertex(VertexProperty('J'), g);

    boost::add_edge(vertexA, vertexB, EdgeProperty(3), g);
    boost::add_edge(vertexB, vertexC, EdgeProperty(2), g);
    boost::add_edge(vertexB, vertexD, EdgeProperty(1), g);
    boost::add_edge(vertexD, vertexE, EdgeProperty(1), g);
    boost::add_edge(vertexC, vertexH, EdgeProperty(2), g);
    boost::add_edge(vertexE, vertexF, EdgeProperty(1), g);
    boost::add_edge(vertexF, vertexG, EdgeProperty(1), g);
    boost::add_edge(vertexG, vertexH, EdgeProperty(1), g);
    boost::add_edge(vertexF, vertexH, EdgeProperty(2), g);
    boost::add_edge(vertexH, vertexI, EdgeProperty(2), g);
    boost::add_edge(vertexH, vertexJ, EdgeProperty(1), g);
    // boost::write_graphviz(std::cout, g, boost::make_label_writer(boost::get(boost::vertex_name, g)));

    std::ofstream outputFile("graph.dot");
    boost::write_graphviz(outputFile, g, boost::make_label_writer(boost::get(boost::vertex_name, g)), boost::make_label_writer(boost::get(boost::edge_weight, g)));
    outputFile.close();
    std::cout << "Graph written to graph.dot" << std::endl;

    auto shortestPathsA = Dijkstra(g, vertexA);
    std::cout << "Shortest paths from vertex A:" << std::endl;
    for (const auto &pair : shortestPathsA)
    {
        std::cout << "Vertex " << boost::get(boost::vertex_name, g, pair.first) << ": " << pair.second << std::endl;
    }

    auto shortestPathsI = Dijkstra(g, vertexI);
    std::cout << "Shortest path from vertex D to vertex I: " << shortestPathsI[vertexD] << std::endl;
}
