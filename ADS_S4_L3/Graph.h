#pragma once
#include <list>
#include <vector>
using namespace std;

template<typename TVertex, typename TEdge>
class Graph {

    struct Edge {
        TEdge data;
        TVertex dest;

        Edge(const TEdge& data, const TVertex& destination) : data(data), dest(destination) {}

    };

    struct Vertex {
        TVertex data;
        list<Edge> _edges;

        Vertex(const TVertex& data) : data(data) {}
    };

    vector<Vertex> table;
};