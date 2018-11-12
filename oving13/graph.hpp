#ifndef GRAPH_H_ODDERIKF
#define GRAPH_H_ODDERIKF

#include <utility>
#include <vector>
#include <climits>

struct Edge {
    unsigned long from;
    unsigned long to;
    unsigned long time;
    unsigned long length;
    unsigned long speed;
    Edge(unsigned long from, unsigned long to, unsigned long time, unsigned long length, unsigned long speed);
};

struct Vertice {
    std::vector<Edge> edges;
    unsigned long index;
    double lat; // as degrees
    double lng; // as degrees
    double radlat; // as radians
    double radlng; // as radians
    double coslat; // as cos of radians
    double coslng; // as cos of radians

    Vertice(unsigned long index, double lat, double lng);
};

double haversine(Vertice from, Vertice to);

typedef std::vector<Vertice> Graph;

#endif