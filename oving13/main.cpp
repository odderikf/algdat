#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>

#include "dijkstra.hpp"
#include "astar.hpp"
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
        edges.emplace_back(from, to, time, length);
    }
}

std::string centiseconds_to_HHmmssss(unsigned long cs){
    unsigned long hours = cs / 360000;
    cs %= 360000;
    unsigned long minutes = cs / 6000;
    cs %= 6000;
    unsigned long seconds = cs / 100;
    cs %= 100;
    unsigned long centiseconds = cs;

    std::ostringstream s;
    s << hours << ":" << minutes << ":" << seconds << "." << centiseconds;
    return s.str();
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

    const unsigned long START = 359842; // københavn
    const unsigned long GOAL = 1233277; // helsinki

    std::vector<unsigned long> path_dijkstra;
    double distance_dijkstra;
    unsigned long pop_count_dijkstra;
    auto distance_function = [](const Edge &e){
        return e.time;
    };

    auto begin_dijkstra = std::chrono::high_resolution_clock::now();
    //dijkstra(vertices, START, GOAL, distance_function, path_dijkstra, distance_dijkstra, pop_count_dijkstra);
    astar(vertices, START, GOAL, distance_function, [](const unsigned long &, const unsigned long &){return 0;}, path_dijkstra, distance_dijkstra, pop_count_dijkstra);
    auto end_dijkstra = std::chrono::high_resolution_clock::now();

    std::cerr << "dijkstra: " << std::endl;
    std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(end_dijkstra-begin_dijkstra).count() << "ms" << std::endl;
    std::cerr << pop_count_dijkstra << " pops" << std::endl;
    std::cerr << centiseconds_to_HHmmssss(distance_dijkstra) << std::endl;

    std::cerr << std::endl;

    std::vector<unsigned long> path_astar;
    double distance_astar;
    unsigned long pop_count_astar;
    double avg_speed = 16; // m/s
    auto distance_estimate =
        [&avg_speed, &vertices](const unsigned long &v1, const unsigned long &v2){
            return haversine(vertices[v1], vertices[v2]) / (avg_speed);
        };

    do {
        auto begin_astar = std::chrono::high_resolution_clock::now();
        astar(vertices, START, GOAL, distance_function, distance_estimate, path_astar, distance_astar, pop_count_astar);
        auto end_astar = std::chrono::high_resolution_clock::now();

        std::cerr << "astar: " << std::endl;
        std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(end_astar - begin_astar).count() << "ms"
                  << std::endl;
        std::cerr << pop_count_astar << " pops" << std::endl;
        std::cerr << centiseconds_to_HHmmssss(distance_astar) << std::endl;
        std::cerr << "avg speed: " << avg_speed << std::endl;

        avg_speed *= 0.9;
    } while (distance_astar == distance_dijkstra);
    for(auto i : path_dijkstra){
        std::cout << vertices[i].lat << ", " << vertices[i].lng << std::endl;
    }
    std::cout << "DIVIDER" << std::endl;
    for(auto i : path_astar){
        std::cout << vertices[i].lat << ", " << vertices[i].lng << std::endl;
    }


    return EXIT_SUCCESS;
}