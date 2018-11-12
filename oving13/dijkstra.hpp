#ifndef DIJKSTRA_H_ODDERIKF
#define DIJKSTRA_H_ODDERIKF

#include <functional>
#include "graph.hpp"

std::pair<std::vector<unsigned long>, unsigned long> dijkstra(Graph &vertices, const unsigned long &start, const unsigned long &goal, const std::function<double(const Edge &)> &distance);

#endif