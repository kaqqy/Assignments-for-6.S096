#ifndef MST_H
#define MST_H

#include <vector>

class State {
    size_t _node;
    double _dist;
public:
    State(size_t aNode, double aDist) : _node{aNode}, _dist{aDist} {}
    inline size_t node() const { return _node; }
    inline double dist() const { return _dist; }
};

class AdjacencyList {
    std::vector<std::vector<State>> _vert;
    AdjacencyList() = delete;
public:
    AdjacencyList(std::istream &input);
    inline size_t size() const { return _vert.size(); }
    inline const std::vector<State>& vert(size_t node) const { return _vert[node]; }
    double mst();
    void print();
};

#endif
