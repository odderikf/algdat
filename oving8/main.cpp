#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <boost/date_time.hpp>
#include "../mylib/heap.hpp"
#include "../mylib/graph.hpp"
#include "../mylib/dijkstra.hpp"

void load_vertices(const std::string &filename, bool get_r,
                my::Graph &vertices, my::Graph &vertices_r,
                u_int64_t &vertice_count, u_int64_t &edge_count){

    std::cout << "reading file " << filename << std::endl;
    std::fstream file(filename, std::ios::in);

    file >> vertice_count >> edge_count;

    vertices.reserve(static_cast<u_int64_t>(vertice_count));
    for(u_int64_t i = 0; i < vertice_count; i++){
        vertices.emplace_back(my::Vertice(i));
        if (get_r) vertices_r.emplace_back(my::Vertice(i));
    }

    u_int64_t fro, to, weight;
    while (file >> fro >> to >> weight) {
        vertices[fro].edges.emplace_back(to, weight);
        if (get_r) vertices_r[to].edges.emplace_back(fro, weight);
    }
    file.close();
}

std::vector<unsigned long> getpath(std::vector<unsigned long> ancestors, my::Vertice start, my::Vertice end){
    std::vector<unsigned long> path;
    for(auto i = start.index; i != ULONG_MAX; i = ancestors[i]){
        path.emplace_back(i);
    }
    return path;
}

int main(int argc, char* argv[]) {

    std::string filename = "../graphs/vg1";
    if (argc > 1)
        filename = argv[1];

    my::Graph vertices;
    my::Graph vertices_r;
    u_int64_t vertice_count = 0;
    u_int64_t edge_count = 0;

    boost::posix_time::ptime start = boost::posix_time::microsec_clock::local_time();
    load_vertices(filename, true, vertices, vertices_r, vertice_count, edge_count);
    boost::posix_time::ptime end = boost::posix_time::microsec_clock::local_time();
    std::cout << "loaded " << vertices.size() << " vertices in " << (end-start).total_microseconds()/1000000. << " seconds" << std::endl;


    start = boost::posix_time::microsec_clock::local_time();
    auto res = my::dijkstra(vertices, 0);
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
