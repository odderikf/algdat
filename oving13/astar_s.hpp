#ifndef ASTAR_H_ODDERIKF
#define ASTAR_H_ODDERIKF

#include <functional>
#include "graph.hpp"

void astar(const Graph &vertices, const unsigned long &start, const unsigned long &goal,
           std::vector<unsigned long> &path, double &distance, unsigned long &pop_count);


#endif