#ifndef ASTAR_H_ODDERIKF
#define ASTAR_H_ODDERIKF

#include <functional>
#include "graph.hpp"

void astar(Graph &vertices, const unsigned long &start, const unsigned long &goal,
           const std::function<double(const Edge &)> &distance_function,
           const std::function<double(const unsigned long &, const unsigned long &)> &distance_estimate,
           std::vector<unsigned long> &path, double &distance, unsigned long &pop_count);


#endif