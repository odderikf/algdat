#include "graph.hpp"
#include <climits>
#include <cmath>

Vertice::Vertice(unsigned long index, double lat, double lng) : index(index), lat(lat), lng(lng) {
    radlat = lat * M_PI / 180;
    radlng = lng * M_PI / 180;
    coslat = std::cos(radlat);
}

double haversine(const Vertice &from, const Vertice &to) {
    /*
    double r =  6371000; //m
    double first_middle = std::pow( std::sin( (from.radlat - to.radlat)/2.0 ) , 2.0 );
    double second_middle = from.coslat*to.coslat*std::pow( std::sin( (from.radlng - to.radlng)/2.0 ) , 2.0);
    return 2*r*std::asin( std::sqrt( first_middle + second_middle ) );
     */
    return 12742000*std::asin( std::sqrt(
            std::pow( std::sin( (from.radlat - to.radlat)/2.0 ) , 2.0 )
            + from.coslat*to.coslat*std::pow( std::sin( (from.radlng - to.radlng)/2.0 ) , 2.0)
    ) );
}

Edge::Edge(unsigned long from, unsigned long to, unsigned long time, unsigned long length)
: from(from), to(to), time(time), length(length){}
