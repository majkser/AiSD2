#include <iostream>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>

typedef boost::property<boost::vertex_name_t, char> VertexProperty;
typedef boost::property<boost::edge_weight_t, int> EdgeProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty> graph;

void Dijkstra(graph &g)
{
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
}
