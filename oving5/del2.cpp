#include <utility>

#include <fstream>
#include <vector>
#include <iostream>
#include <memory>
#include <random>
#include <algorithm>
#include "../mylib/timeit.hpp"

class HashTable{
public:
    unsigned long hash(long int k){
        return  k%elements.size();
    }
    unsigned long hash2(long int k){
        return k%(elements.size()-1)+1;
    }

    HashTable setCapacity(unsigned long cap){
        elements.reserve(static_cast<unsigned long>(cap));
        while (elements.size()<elements.capacity()){
            elements.push_back(0);
        }
        return *this;
    }
    void add(const long int &key){
        unsigned long hashed = hash(key);
        unsigned long hashed2 = hash2(key);
        while (elements[hashed]){
            if (elements[hashed] == key)
                return; //don't save two values for one key, doesn't make sense.
            kollisjoner++;
            hashed += hashed2;
            hashed %= elements.size();
        }
        _size++;
        elements[hashed] = key;
    }

    long get(const long &key){
        return elements[hash(key)];
    }
    double load(){
        return double(_size) / elements.capacity();
    }

    int kollisjoner = 0;

private:
    unsigned long _size = 0;
    std::vector<long> elements;
};

int dummy(int i){
    return i;
}

int main() {

    unsigned long len = 5000000;
    HashTable table = HashTable()
            .setCapacity(6600001);

    std::map<long, long> map;

    std::unordered_map<long, long> umap;
    umap.reserve(len);

    std::random_device device;
    std::mt19937_64 mers {device()};
    std::uniform_int_distribution<long> dist {LONG_MIN, LONG_MAX};
    auto gen = [&dist, &mers](){
        return dist(mers);
    };
    long double mytime;
    long double maptime;
    long double umaptime;
    std::vector<long> numbers(len);
    std::generate( std::begin(numbers), std::end(numbers), gen);

    mytime = my::timeit([&table](std::vector<long> l){
        for(auto j : l) table.add(j);
        }, numbers);

    maptime = my::timeit([&map](std::vector<long> l) {
        for (auto j : l) map.emplace(j, j);
        }, numbers);

    umaptime = my::timeit([&umap](std::vector<long> l) {
        for (auto j : l) umap.emplace(j, j);
        }, numbers);

    std::cout << "my: " << mytime << std::endl;
    std::cout << "map: " << maptime << std::endl;
    std::cout << "umap: " << umaptime << std::endl;
    std::cout << "load faktor: " << table.load() << std::endl;
    std::cout << "kollisjoner: " << table.kollisjoner << std::endl;


}
