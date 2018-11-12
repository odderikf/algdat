#ifndef GRAPH_H_ODDERIKF
#define GRAPH_H_ODDERIKF

#include <utility>
#include <vector>

namespace my {

    class Vertice;

    typedef std::pair<unsigned long, unsigned long> Edge;

    class Vertice {
    public:
        std::vector<Edge> edges;
        unsigned long index;
        unsigned long distance;

        Vertice(unsigned long i);

        bool operator==(Vertice that) const;

        bool operator>(Vertice that) const;

        bool operator<(Vertice that) const;

        Vertice &operator=(const Vertice &that);

        Vertice(const Vertice &that);
    };

    typedef std::vector<Vertice> Graph;
}

#endif