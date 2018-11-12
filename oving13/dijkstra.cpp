#include "dijkstra.hpp"
#include "../mylib/heap.hpp"
#include <iostream>
#include <climits>
#include <cfloat>

void dijkstra(Graph &vertices, const unsigned long &start, const unsigned long &goal,
        const std::function<double(const Edge &)> &distance_function,
        std::vector<unsigned long> &path, double &distance, unsigned long &pop_count) {

    pop_count = 0;
    std::vector<double> distances;
    std::vector<unsigned long> ancestors;
    std::vector<unsigned long> internal;
    std::vector<bool> found;
    distances.reserve(vertices.size());
    ancestors.reserve(vertices.size());
    internal.reserve(vertices.size());
    for (unsigned long i = 0; i < vertices.size(); i++) {
        distances.emplace_back(DBL_MAX);
        ancestors.emplace_back(ULONG_MAX);
        found.emplace_back(false);
    }
    distances[start] = 0;
    internal.emplace_back(start);
    std::function<bool(const unsigned long &, const unsigned long &)> lessthan;
    lessthan = [ &distances ](const unsigned long &v1, const unsigned long &v2){
        return distances[v1] < distances[v2];
    };
    my::Heap<unsigned long> stack(internal, my::Heap<unsigned long>::MIN_HEAP, lessthan);
    while (not stack.empty()) { // N
        auto v = stack.pop(); //
        pop_count++;
        if (found[v]) {
            continue;
        }
        found[v] = true;
        for (auto c : vertices[v].edges) {
            if (found[c.to]) continue;
            double altdist = distances[v] + distance_function(c); // distance to v + length of edge between c and v.
            auto v2 = c.to;
            stack.emplace(v2);
            if (altdist < distances[v2]) {
                distances[v2] = altdist;
                ancestors[v2] = v;
            }
        }
        if (v == goal) break;
    }

    path.emplace_back(goal);
    auto current = goal;
    while (current != start){
        current = ancestors[current];
        path.emplace_back(current);
    }
    std::reverse(path.begin(), path.end());
    distance = distances[goal];
}
