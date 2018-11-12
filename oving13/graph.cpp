#include "graph.hpp"
#include <climits>
#include <cmath>

Vertice::Vertice(unsigned long index, double lat, double lng) : index(index), lat(lat), lng(lng) {
    radlat = lat * M_PI / 180;
    radlng = lng * M_PI / 180;
    coslat = std::cos(radlat * M_PI / 180);
    coslng = std::cos(radlng * M_PI / 180);
}

double haversine(Vertice from, Vertice to) {
    double r =  6371; //km
    double first_middle = std::pow( std::sin( (from.radlat - to.radlat)/2 ) , 2 );
    double second_middle = from.coslat*to.coslat*std::pow( std::sin( (from.radlng - to.radlng)/2 ) , 2);
    return 2*r*std::asin( std::sqrt( first_middle + second_middle ) );
}

Edge::Edge(unsigned long from, unsigned long to, unsigned long time, unsigned long length, unsigned long speed)
: from(from), to(to), time(time), length(length), speed(speed){}
