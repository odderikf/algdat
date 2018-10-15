#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <boost/date_time.hpp>
#include "../mylib/heap.hpp"

class Vertice;
typedef std::pair<unsigned long, unsigned long> Edge;
class Vertice{
public:
    std::vector<Edge> edges;
    unsigned long index;
    unsigned long distance;

    Vertice(unsigned long i) : index(i), distance(ULONG_MAX) {}
    bool operator==(Vertice that) const{
        return this->index == that.index;
    }
    bool operator>(Vertice that) const{
        return this->distance > that.distance;
    }
    bool operator<(Vertice that) const{
        return this->distance < that.distance;
    }
    Vertice &operator=(const Vertice &that){
        edges = that.edges;
        index = that.index;
        distance = that.distance;
    }
    Vertice(const Vertice &that){
        edges = that.edges;
        index = that.index;
        distance = that.distance;
    }
};
typedef std::vector<Vertice> Graph;

void load_vertices(const std::string &filename, bool get_r,
                Graph &vertices, Graph &vertices_r,
                u_int64_t &vertice_count, u_int64_t &edge_count){

    std::cout << "reading file " << filename << std::endl;
    std::fstream file(filename, std::ios::in);

    file >> vertice_count >> edge_count;

    vertices.reserve(static_cast<u_int64_t>(vertice_count));
    for(u_int64_t i = 0; i < vertice_count; i++){
        vertices.emplace_back(Vertice(i));
        if (get_r) vertices_r.emplace_back(Vertice(i));
    }

    u_int64_t fro, to, weight;
    while (file >> fro >> to >> weight) {
        vertices[fro].edges.emplace_back(to, weight);
        if (get_r) vertices_r[to].edges.emplace_back(fro, weight);
    }
    file.close();
}

std::pair<std::vector<unsigned long>, std::vector<unsigned long>>
dijkstra(Graph &vertices, const unsigned long &start){

    std::vector<unsigned long> distances;
    std::vector<unsigned long> ancestors;
    std::vector<Vertice> internal;
    std::vector<bool> found;
    distances.reserve(vertices.size());
    ancestors.reserve(vertices.size());
    internal.reserve(vertices.size());
    for(unsigned long i = 0; i < vertices.size(); i++){
        distances.emplace_back(ULONG_MAX);
        ancestors.emplace_back(ULONG_MAX);
        found.emplace_back(false);
    }
    distances[start] = 0;
    internal.emplace_back(vertices[start]);
    internal[0].distance = 0;
    my::Heap<Vertice> stack(internal, my::Heap<Vertice>::MIN_HEAP);
    int counter = 0;
    int permille = stack.size/1000;
    int permillecounter = 0;
    while (not stack.empty()){ // N
        auto v = stack.pop(); //
        if (found[v.index]){
            continue;
        }
        found[v.index] = true;
        counter++;
        if (counter == permille){
            counter = 0;
            permillecounter++;
            std::cout << "\r" << permillecounter/10. << "%" << std::flush;
        }
        for(auto c : v.edges) {
            if (v.distance != ULONG_MAX) {
                unsigned long altdist = v.distance + c.second; // distance to v + length of edge between c and v.
                auto v2 = vertices[c.first];
                if (altdist < distances[v2.index]) {
                    distances[v2.index] = altdist;
                    ancestors[v2.index] = v.index;
                    Vertice newV = v2;
                    newV.distance = altdist;
                    stack.emplace(newV);
                    vertices[c.first].distance = altdist;
                }
            }
        }
    }
    std::cout << std::endl;

    return std::pair<std::vector<unsigned long int>,std::vector<unsigned long int>>(ancestors,distances);
}

std::vector<unsigned long> getpath(std::vector<unsigned long> ancestors, Vertice start, Vertice end){
    std::vector<unsigned long> path;
    for(auto i = start.index; i != ULONG_MAX; i = ancestors[i]){
        path.emplace_back(i);
    }
    return path;
}

int main(int argc, char* argv[]) {

    std::string filename = "../graphs/vgSkandinavia";
    if (argc > 1)
        filename = argv[1];

    Graph vertices;
    Graph vertices_r;
    u_int64_t vertice_count = 0;
    u_int64_t edge_count = 0;

    boost::posix_time::ptime start = boost::posix_time::microsec_clock::local_time();
    load_vertices(filename, true, vertices, vertices_r, vertice_count, edge_count);
    boost::posix_time::ptime end = boost::posix_time::microsec_clock::local_time();
    std::cout << "loaded " << vertices.size() << " vertices in " << (end-start).total_microseconds()/1000000. << " seconds" << std::endl;


    start = boost::posix_time::microsec_clock::local_time();
    auto res = dijkstra(vertices, 0);
    auto ancestors = res.first;
    auto distances = res.second;
    end = boost::posix_time::microsec_clock::local_time();
    std::cout << "found dijkstra in " << (end-start).total_microseconds()/1000000. << " seconds" << std::endl;

    if (ancestors.size() < 10000000){
        std::string tab = "\t\t\t";
        std::cout << "Node" << "\t" << "ancestor" << "\t" << "distance" << std::endl;
        for(u_int64_t i = 0; i < ancestors.size() and i < 100; i++){
            std::cout << i << tab;
            if (ancestors[i] != ULONG_MAX) {
                std::cout << ancestors[i];
            } else {
                std::cout << " ";
            }
            std::cout << tab;
            if (distances.at(i) != ULONG_MAX) {
                 std::cout << distances[i];
            } else {
                std::cout << "unreachable";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "Path from " << 50 << " to " << 0 << std::endl;
    for(auto i : getpath(ancestors, 50, 0)){
        std::cout << i;
        if (i != 0) std::cout << ", ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;


}
