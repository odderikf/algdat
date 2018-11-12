#ifndef DIJKSTRA_H_ODDERIKF
#define DIJKSTRA_H_ODDERIKF

#include "graph.hpp"
namespace my {
    std::pair<std::vector<unsigned long>, std::vector<unsigned long>>
    dijkstra(my::Graph &vertices, const unsigned long &start);
}

#endif