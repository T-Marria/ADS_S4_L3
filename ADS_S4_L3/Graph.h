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
        list<Edge> edges;

        Vertex(const TVertex& data) : data(data) {}
    };

    vector<Vertex> table;

public:
    int index(const TVertex& data) const {
        for (int i = 0; i < table.size(); ++i) {
            if (table[i].data == data) return i;
        }
        return -1;
    }

    void add_vertex(const TVertex& data) {
        if (index(data) == -1) {
            table.push_back(Vertex(data));
        }
        else throw exception();
    }

    void add_edge(const TVertex& from_data, const TVertex& to_data, const TEdge& new_edge) {
        int from_id = index(from_data);
        int to_id = index(to_data);
        if ((from_id == -1) || (to_id == -1)) throw exception();
        table[from_id].edges.push_back(Edge(new_edge, to_data));
    }

    void delete_vertex(const TVertex& data) {
        int vert_id = index(data);
        if (vert_id == -1) throw std::exception();
        for (auto vert_it = table.begin(); vert_it != table.end(); ) {
            if (vert_it->data == data) {
                vert_it = table.erase(vert_it);
            }
            else {
                for (auto edge_it = (*vert_it).edges.begin();
                    edge_it != (*vert_it).edges.end(); ) {
                    if (edge_it->_dst == data) edge_it = (*vert_it).edges.erase(edge_it);
                    else ++edge_it;
                }
                ++vert_it;
            }
        }
    }

    void delete_edge(const TVertex& from_data, const TVertex& to_data) {
        int from_id = index(from_data);
        int to_id = index(to_data);
        if ((from_id == -1) || (to_id == -1)) throw std::exception();
        for (auto it = table[from_id].edges.begin(); it != table[from_id].edges.end(); ) {
            if (it->_dst == to_data) {
                table[from_id].edges.erase(it);
                break;
            }
            else ++it;
        }
    }
    
    // TODO: add graph printing
};