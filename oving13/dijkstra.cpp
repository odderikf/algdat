#include "dijkstra.hpp"
#include "../mylib/heap.hpp"
#include <iostream>
#include <climits>
#include <cfloat>

std::pair<std::vector<unsigned long>, unsigned long> dijkstra(Graph &vertices, const unsigned long &start, const unsigned long &goal,
        const std::function<double(const Edge &)> &distance) {

    std::vector<double> distances;
    std::vector<unsigned long> ancestors;
    std::vector<Vertice> internal;
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
    internal.emplace_back(vertices[start]);
    std::function<bool(const Vertice &, const Vertice &)> lessthan;
    lessthan = [ &distances ](const Vertice &v1, const Vertice &v2){
        return distances[v1.index] < distances[v2.index];
    };
    my::Heap<Vertice> stack(internal, my::Heap<Vertice>::MIN_HEAP, lessthan);
    int counter = 0;
    int permille = stack.size / 1000;
    int permillecounter = 0;
    while (not stack.empty()) { // N
        auto v = stack.pop(); //
        if (found[v.index]) {
            continue;
        }
        found[v.index] = true;
        counter++;
        if (counter == permille) {
            counter = 0;
            permillecounter++;
        }
        for (auto c : v.edges) {
            if (found[c.to]) continue;
            double altdist = distances[v.index] + distance(c); // distance to v + length of edge between c and v.
            auto v2 = vertices[c.to];
            stack.emplace(v2);
            if (altdist < distances[v2.index]) {
                distances[v2.index] = altdist;
                ancestors[v2.index] = v.index;
            }
        }
        if (v.index == goal) break;
    }

    std::vector<unsigned long> path;
    path.emplace_back(goal);
    auto current = goal;
    while (current != start){
        current = ancestors[current];
        path.emplace_back(current);
    }
    std::reverse(path.begin(), path.end());
    return std::pair(path, distances[goal]);//std::pair<std::vector<unsigned long int>, std::vector<unsigned long int>>(ancestors, distances);
}
