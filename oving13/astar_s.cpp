#include "astar_s.hpp"
#include "../mylib/heap.hpp"
#include <iostream>
#include <climits>
#include <cfloat>

void astar(const Graph &vertices, const unsigned long &start, const unsigned long &goal,
        std::vector<unsigned long> &path, double &distance, unsigned long &pop_count) {

    pop_count = 0;
    std::vector<double> distances(vertices.size(), DBL_MAX);
    std::vector<double> haversines(vertices.size(), DBL_MAX);
    std::vector<unsigned long> ancestors(vertices.size(), ULONG_MAX);
    std::vector<bool> found(vertices.size(), false);
    std::vector<unsigned long> internal;
    internal.reserve( vertices.size()/2 );

    distances[start] = 0;
    haversines[start] = haversine(vertices[start], vertices[goal]);

    internal.emplace_back(start);

    std::function<bool(const unsigned long &, const unsigned long &)> lessthan;
    lessthan = [ &distances, &haversines, &vertices, &goal](const unsigned long &v1, const unsigned long &v2){
        return distances[v1] + haversines[v1] < distances[v2] + haversines[v2];
    };

    my::Heap<unsigned long> stack(internal, my::Heap<unsigned long>::MIN_HEAP, lessthan);
    while (not stack.empty()) {
        auto v = stack.pop();
        pop_count++;
        if (found[v]) {
            continue;
        }
        found[v] = true;
        if (v == goal) break;
        for (auto c : vertices[v].edges) {
            double altdist = distances[v] + c.time; // distance to v + length of edge between c and v.
            auto v2 = c.to;
            if (altdist < distances[v2]) {
                distances[v2] = altdist;
                ancestors[v2] = v;
                haversines[v2] = haversine(vertices[v2], vertices[goal]) * (3.69609856);
                stack.emplace(v2);
            }
            else if (not found[v2]) {
                haversines[v2] = haversine(vertices[v2], vertices[goal]) * (3.69609856);
                stack.emplace(v2);
            }
        }
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
