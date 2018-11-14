#include "astar.hpp"
#include "../mylib/heap.hpp"
#include <iostream>
#include <climits>
#include <cfloat>

void astar(Graph &vertices, const unsigned long &start, const unsigned long &goal,
        const std::function<double(const Edge &)> &distance_function,
        const std::function<double(const unsigned long &, const unsigned long &)> &distance_estimate,
        std::vector<unsigned long> &path, double &distance, unsigned long &pop_count) {

    pop_count = 0;
    std::vector<double> distances;
    std::vector<unsigned long> ancestors;
    std::vector<bool> found;
    std::vector<unsigned long> internal;

    distances.reserve(vertices.size());
    ancestors.reserve(vertices.size());
    found.reserve(    vertices.size());
    internal.reserve( vertices.size()/2);

    std::fill(distances.begin(), distances.begin() + vertices.size(), DBL_MAX);
    std::fill(ancestors.begin(), ancestors.end()   + vertices.size(), ULONG_MAX);
    std::fill(found.begin(),     found.end()       + vertices.size(), false);

    distances[start] = 0;

    internal.emplace_back(start);

    std::function<bool(const unsigned long &, const unsigned long &)> lessthan;
    lessthan = [ &distances, &distance_estimate, &goal](const unsigned long &v1, const unsigned long &v2){
        return distances[v1] + distance_estimate(v1, goal) < distances[v2] + distance_estimate(v2, goal);
    };

    my::Heap<unsigned long> stack(internal, my::Heap<unsigned long>::MIN_HEAP, lessthan);
    while (not stack.empty()) { // N
        auto v = stack.pop(); //
        if (found[v]) {
            continue;
        }
        pop_count++;
        found[v] = true;
        if (v == goal) break;
        for (auto c : vertices[v].edges) {
            //if (found[c.to]) continue;
            double altdist = distances[v] + distance_function(c); // distance to v + length of edge between c and v.
            auto v2 = c.to;
            if (altdist < distances[v2]) {
                distances[v2] = altdist;
                ancestors[v2] = v;
            }
            stack.emplace(v2);
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
