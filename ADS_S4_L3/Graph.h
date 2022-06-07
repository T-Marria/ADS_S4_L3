#pragma once
#include <utility>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <map>
#include <exception>
#include <iostream>
using namespace std;


template<typename TVertex, typename TEdge>
class Graph {

    struct edge {
        TEdge data;
        TVertex dest;

        edge(const TEdge& data, const TVertex& destination) : data(data), dest(destination) {}

    };

    struct search_info {
        int color = 0;
        TVertex prev;
        int t_open = 0;
        int t_close = 0;
    };

    struct vertex {
        TVertex data;
        list<edge> edges;
        search_info info;

        vertex(const TVertex& data) : data(data) {}
    };

    vector<vertex> table;

    void _deep_search(const TVertex& data, int& t) { // внутренняя функция для поиска
        int start_id = index(data);
        table[start_id].info.color = 1;
        table[start_id].info.t_open = t;
        t++;
        for (auto it = table[start_id].edges.begin(); it != table[start_id].edges.end(); it++) {
            int next_id = index(it->dest);
            if (table[next_id].info.color == 0) {
                table[next_id].info.prev = table[start_id].data;
                _deep_search(table[next_id].data, t);
            }
        }
        table[start_id].info.color = 1;
        table[start_id].info.t_close = t;
        table[start_id].data.print_town();
        t++;
    }

public:
    int index(const TVertex& data) const {
        for (int i = 0; i < table.size(); ++i) {
            if (table[i].data == data) return i;
        }
        return -1;
    }

    void add_vertex(const TVertex& data) {
        if (index(data) == -1) {
            table.push_back(vertex(data));
        }
        else throw exception();
    }

    void add_edge(const TVertex& from_data, const TVertex& to_data, const TEdge& new_edge) {
        int from_id = index(from_data);
        int to_id = index(to_data);
        if ((from_id == -1) || (to_id == -1)) throw exception();
        table[from_id].edges.push_back(edge(new_edge, to_data));
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

    void deep_search() {    // основная функция алгоритма обхода
        int t = 0;
        _deep_search(table[0].data, t);
        for (auto vert_it = table.begin(); vert_it != table.end(); vert_it++) {
            if ((*vert_it).info.color == 0) {
                _deep_search((*vert_it).data, t);
            }
        }
    }

    // TODO: add bellman ford algorithm

    void print() {
        for (size_t i = 0; i < table.size(); ++i) {
            cout << "information about the town: " << endl;
            table[i].data.print_town();
            cout << "The roads from this town:" << endl;
            if (table[i].edges.begin() == table[i].edges.end()) {
                cout << "There are no roads" << endl;
            }
            for (auto elem : table[i].edges) {
                cout << "\t" << "Name of road: " << elem.data.get_name() << "  Length: " << elem.data.get_length() << endl;
            }
            cout << endl;
        }
    }


};