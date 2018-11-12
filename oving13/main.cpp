#include <iostream>
#include <fstream>
#include <chrono>

#include "dijkstra.hpp"
#include "graph.hpp"
#include "../mylib/heap.hpp"

void load_vertices(std::ifstream &file, Graph &vertices){
    unsigned long index, node_count;
    double lat, lng;
    file >> node_count;
    vertices.reserve(node_count);

    while (file >> index >> lat >> lng){
        vertices.emplace_back(index, lat, lng);
    }
}

void load_edges(std::ifstream &file, std::vector<Edge> &edges){
    unsigned long edge_count, from, to, time, length, speed;
    file >> edge_count;
    edges.reserve(edge_count);

    while (file >> from >> to >> time >> length >> speed){
        edges.emplace_back(from, to, time, length, speed);
    }
}
int main(){
    std::string noder = "../graph/noder.txt";
    std::string kanter = "../graph/kanter.txt";

    std::ifstream noder_file;
    noder_file.open(noder, std::ios::in);
    Graph vertices;
    load_vertices(noder_file, vertices);
    noder_file.close();

    std::ifstream kanter_file;
    kanter_file.open(kanter);
    std::vector<Edge> edges;
    load_edges(kanter_file, edges);
    kanter_file.close();

    for(auto e : edges){
        vertices[e.from].edges.emplace_back(e);
    }

    std::function<double(const Edge &)> distance_function = [](const Edge &e){return e.time;};
    auto begin = std::chrono::high_resolution_clock::now();
    auto p = dijkstra(vertices, 2447613, 4043636, distance_function);
    auto end = std::chrono::high_resolution_clock::now();
    std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() << "ms" << std::endl;
    auto path = p.first;
    auto distance = p.second;

    for( auto v : path ){
        std::cout << vertices[v].lat << ", " << vertices[v].lng << std::endl;
    }


    return EXIT_SUCCESS;
}