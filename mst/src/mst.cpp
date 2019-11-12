#include "mst.h"

#include <iostream>
#include <queue>
#include <unordered_map>

bool operator<(const State &a, const State &b) {
    return a.dist() > b.dist();
}

AdjacencyList::AdjacencyList(std::istream &input) {
    size_t numVert, numEdge;
    input >> numVert >> numEdge;
    _vert.resize(numVert);
    for (size_t i = 0; i < numEdge; i++) {
        int s, t;
        double w;
        input >> s >> t >> w;
        _vert[s].push_back(State(t, w));
        _vert[t].push_back(State(s, w));
    }
}

double AdjacencyList::mst() {
    double mstWeight = 0.0;
    size_t numVert = size();
    std::priority_queue<State> toVisit;
    std::unordered_map<int, bool> visited;
    toVisit.push(State(0, 0.0));
    while (visited.size() < numVert) {
        State top = toVisit.top();
        toVisit.pop();
        if (visited[top.node()]) {
            continue;
        }
        visited[top.node()] = true;
        mstWeight += top.dist();
        for (auto n : _vert[top.node()]) {
            toVisit.push(n);
        }
    }
    return mstWeight;
}
