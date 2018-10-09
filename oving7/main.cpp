#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <set>
#include <stack>
#include <algorithm>
#include <boost/date_time.hpp>

typedef std::vector<std::set<unsigned long>> Graph;

std::stack<unsigned long> topological(Graph vertices, unsigned long vertice_count){

    std::cout << ("finding topological") << std::endl;
    std::set<unsigned long> notfound;
    for(unsigned long i=0;i<vertices.size();i++) notfound.emplace(i);
    std::set<unsigned long> found;
    std::stack<unsigned long> topo;
    std::stack<std::pair<unsigned long, bool>> stack;

    while (topo.size() < vertices.size()){
        if (stack.empty()){
            auto p = notfound.begin();
            stack.emplace(*p, false);
        }
        std::pair<unsigned long,bool> holder = stack.top();
        stack.pop();
        unsigned long i = holder.first;
        bool backtracking = holder.second;
        auto pos = found.find(i);
        if (not backtracking and pos == found.end()){
            notfound.erase(notfound.find(i));
            found.emplace(i);
            std::set<unsigned long> children = vertices[i];
            for(auto p = children.begin(); p != children.end(); p++){ // remove found children
                if (found.find(*p) != found.end()){
                    children.erase(p);
                }
            }
            if(not children.empty()){
                stack.emplace(i, true);
                for (unsigned long v : children){
                    stack.emplace(v, false);
                }
            } else {
                topo.emplace(i);
            }
        } else if (backtracking){
            topo.emplace(i);
        }

    }
    return topo;
}

void load_vertices(const std::string &filename, bool get_r,
        Graph &vertices, Graph &vertices_r
                ,unsigned long &vertice_count, unsigned long &edge_count){

    std::cout << "reading file" << std::endl;
    std::fstream file(filename, std::ios::in);

    file >> vertice_count >> edge_count;

    vertices.reserve(static_cast<unsigned long>(vertice_count));
    vertices_r.reserve(static_cast<unsigned long>(vertice_count));
    for(unsigned long _ = 0; _ < vertice_count; _++){
        vertices.emplace_back(std::set<unsigned long>());
        if (get_r) vertices_r.emplace_back(std::set<unsigned long>());
    }

    unsigned long to, fro;
    while (file >> to >> fro) {
        vertices[to].emplace(fro);
        if (get_r) vertices_r[fro].emplace(to);
    }
    file.close();
}


std::vector<std::vector<unsigned long>> findComponents(Graph vertices, unsigned long vertice_count, std::stack<unsigned long> order){
    std::cout << "finding components" << std::endl;
    std::vector<unsigned long> nodecomp;
    nodecomp.reserve(static_cast<unsigned long>(vertice_count));
    for(unsigned long _ = 0; _ < vertice_count; _++) nodecomp.emplace_back(-1);
    unsigned long comp = 0;

    while (not order.empty()){
        unsigned long v = order.top();
        order.pop();

        if (nodecomp[v] == -1){
            std::set<unsigned long> children = vertices[v];
            nodecomp[v] = comp;
            while (not children.empty()){
                auto p = children.begin();
                unsigned long c = *p;
                children.erase(p);
                if (nodecomp[c] == -1){
                    nodecomp[c] = comp;
                    std::set<unsigned long> subch = vertices[c];
                    for (unsigned long i : subch) children.emplace(i);

                }
            }
            comp++;
        }

    }
    std::vector<std::vector<unsigned long>> result;
    result.reserve(static_cast<unsigned long>(comp));
    for(unsigned long _ = 0; _ < comp; _++) result.emplace_back(std::vector<unsigned long>());
    for(unsigned long i = 0; i < nodecomp.size(); i++){
        unsigned long v = nodecomp[i];
        result[v].emplace_back(i);
    }
    return result;

}


int main(int argc, char* argv[]) {

    std::string filename = "L7g2";
    if (argc > 1)
        filename = argv[1];

    Graph vertices;
    Graph vertices_r;
    unsigned long vertice_count = 0;
    unsigned long edge_count = 0;

    boost::posix_time::ptime start = boost::posix_time::microsec_clock::local_time();
    load_vertices(filename, true, vertices, vertices_r, vertice_count, edge_count);
    boost::posix_time::ptime end = boost::posix_time::microsec_clock::local_time();
    std::cout << "loaded " << vertices.size() << " vertices in " << (end-start).total_microseconds()/1000000. << " seconds" << std::endl;

    start = boost::posix_time::microsec_clock::local_time();
    std::stack<unsigned long> topo = topological(vertices, vertice_count);
    end = boost::posix_time::microsec_clock::local_time();
    auto ostart = start;
    std::cout << "found topological order in " << (end-start).total_microseconds()/1000000. << " seconds" << std::endl;

    start = boost::posix_time::microsec_clock::local_time();
    auto strongs = findComponents(vertices_r, vertice_count, topo);
    end = boost::posix_time::microsec_clock::local_time();
    std::cout << "found components in " << (end-start).total_microseconds()/1000000. << " seconds" << std::endl;
    std::cout << "total time: " << (end-ostart).total_microseconds()/1000000 << " seconds" << std::endl;


    std::cout << "grafen " << filename << " har " << strongs.size() << " sterkt sammenhengende komponenter." << std::endl;
    if (strongs.size() < 100){
        std::cout << "Komponent\t\tNoder i komponenten" << std::endl;
        for(unsigned long i = 0; i < strongs.size(); i++){
            std::vector<unsigned long> v = strongs[i];
            std::cout << i << "\t\t\t\t";
            for(unsigned long j = 0; j < v.size(); j++){
                std::cout << v[j];
                if (j+1 < v.size()) std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }

    return EXIT_SUCCESS;


}
