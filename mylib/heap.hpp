#ifndef HEAP_H_ODDERIKF
#define HEAP_H_ODDERIKF


#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

namespace my {

    template <typename T>
    class Heap {
    public:
        static const bool MAX_HEAP = true;
        static const bool MIN_HEAP = false;
        bool max_or_min = MAX_HEAP;

        Heap(std::vector<T> &, bool, std::function<bool(const T&, const T&)>);
        Heap(std::vector<T> &, bool);
        Heap(bool);
        Heap(bool, std::function<bool(const T&, const T&)>);
        Heap(std::vector<T> &);
        Heap();
        void fix(u_int64_t i);

        u_int64_t left(const u_int64_t &i) const;
        u_int64_t right(const u_int64_t &i) const;
        u_int64_t parent(const u_int64_t &i) const;
        u_int64_t size;
        bool isleaf(const u_int64_t &i) const;
        T pop_max();
        T pop_min();
        T pop();
        bool empty();
        void emplace(T);
        void shrink_to_fit();

        std::function<bool(const T &, const T &)> lessthan;

        void reserve( u_int64_t );

    private:
        std::vector<T> &v;
    };

    template<typename T>
    void heapsort(std::vector<T> *vector){
        my::Heap<T> h = my::Heap<T>(*vector);
        while(not h.isleaf(0)){
            h.pop_max();
        }
    }

    template<typename T>
    void heapsort(std::vector<T> *vector, std::function<bool(const T &, const T &)> lessthan){
        my::Heap<T> h = my::Heap<T>(*vector, lessthan);
        while(not h.isleaf(0)){
            h.pop_max();
        }
    }

    #include "heap_impl.hpp"
}


#endif