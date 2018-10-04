#ifndef HEAP_H_ODDERIKF
#define HEAP_H_ODDERIKF


#include <vector>
#include <algorithm>
namespace my {
    template <typename T>
    class Heap {
    public:
        Heap(std::vector<T> &vec);
        void fix(u_int64_t i);
        u_int64_t left(const u_int64_t &i) const;
        u_int64_t right(const u_int64_t &i) const;
        u_int64_t size;
        bool isleaf(const u_int64_t &i) const;
        T pop_max();
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

}
#endif