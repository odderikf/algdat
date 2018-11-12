#include "graph.hpp"
#include <climits>

namespace my{

    Vertice::Vertice(unsigned long i) : index(i), distance(ULONG_MAX) {}
    bool Vertice::operator==(Vertice that) const{
        return this->index == that.index;
    }
    Vertice::Vertice(const Vertice &that){
        edges = that.edges;
        index = that.index;
        distance = that.distance;
    }
    bool Vertice::operator>(Vertice that) const{
        return this->distance > that.distance;
    }
    bool Vertice::operator<(Vertice that) const{
        return this->distance < that.distance;
    }
    Vertice &Vertice::operator=(const Vertice &that) = default;
}
