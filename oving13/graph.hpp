#ifndef GRAPH_H_ODDERIKF
#define GRAPH_H_ODDERIKF

#include <utility>
#include <vector>
#include <climits>

struct Edge {
    unsigned long from;
    unsigned long to;
    unsigned long time;
    double length;
    Edge(unsigned long from, unsigned long to, unsigned long time, unsigned long length);
};

struct Vertice {
    std::vector<Edge> edges;
    unsigned long index;
    double lat; // as degrees
    double lng; // as degrees
    double radlat; // as radians
    double radlng; // as radians
    double coslat; // as cos of radians

    Vertice(unsigned long index, double lat, double lng);
};

double haversine(const Vertice &from, const Vertice &to);

typedef std::vector<Vertice> Graph;

#endif