#include "dijkstra.hpp"
#include "heap.hpp"
#include <iostream>
#include <climits>

namespace my {
    std::pair<std::vector<unsigned long>, std::vector<unsigned long>>
    dijkstra(my::Graph &vertices, const unsigned long &start) {

        std::vector<unsigned long> distances;
        std::vector<unsigned long> ancestors;
        std::vector<my::Vertice> internal;
        std::vector<bool> found;
        distances.reserve(vertices.size());
        ancestors.reserve(vertices.size());
        internal.reserve(vertices.size());
        for (unsigned long i = 0; i < vertices.size(); i++) {
            distances.emplace_back(ULONG_MAX);
            ancestors.emplace_back(ULONG_MAX);
            found.emplace_back(false);
        }
        distances[start] = 0;
        internal.emplace_back(vertices[start]);
        internal[0].distance = 0;
        my::Heap<my::Vertice> stack(internal, my::Heap<my::Vertice>::MIN_HEAP);
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
                std::cout << "\r" << permillecounter / 10. << "%" << std::flush;
            }
            for (auto c : v.edges) {
                if (v.distance != ULONG_MAX) {
                    unsigned long altdist = v.distance + c.second; // distance to v + length of edge between c and v.
                    auto v2 = vertices[c.first];
                    if (altdist < distances[v2.index]) {
                        distances[v2.index] = altdist;
                        ancestors[v2.index] = v.index;
                        my::Vertice newV = v2;
                        newV.distance = altdist;
                        stack.emplace(newV);
                        vertices[c.first].distance = altdist;
                    }
                }
            }
        }
        std::cout << std::endl;

        return std::pair<std::vector<unsigned long int>, std::vector<unsigned long int>>(ancestors, distances);
    }
}
