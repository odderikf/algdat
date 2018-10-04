#include "heap.hpp"

template<typename T>
my::Heap<T>::Heap(std::vector<T> &vec) : v(vec), size(vec.size()) {
    for(int64_t i = (size-2)/2; i >= 0; i--){
        fix(i);
    }
}

template<typename T>
void my::Heap<T>::fix(u_int64_t n) {
     u_int64_t max = n, l = left(n), r = right(n);


     if( l < size ) {
         if (v[l] > v[max]) max = l;

         if( r < size ) {
             if (v[r] > v[max]) max = r;
         }
         if( max != n ){
             std::swap(v[max], v[n]);
             fix(max);
         }
     }

}

template<typename T>
u_int64_t my::Heap<T>::left(const u_int64_t &i) const {
    return 2 * i + 1;
}

template<typename T>
u_int64_t my::Heap<T>::right(const u_int64_t &i) const {
    return 2 * i + 2;
}

template<typename T>
T my::Heap<T>::pop_max() {
    std::swap(v[--size], v[0]);
    T val = v[size];
    fix(0);
    return val;
}

template<typename T>
bool my::Heap<T>::isleaf(const u_int64_t &i) const {
    return 2*i + 1 > size;
}
