#ifndef DIJKSTRA_H_ODDERIKF
#define DIJKSTRA_H_ODDERIKF

#include <functional>
#include "graph.hpp"

void dijkstra(Graph &vertices, const unsigned long &start, const unsigned long &goal,
                const std::function<double(const Edge &)> &distance_function,
                 std::vector<unsigned long> &path, double &distance, unsigned long &pop_count);

#endif