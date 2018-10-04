#ifndef SORT_H_ODDERIKF
#define SORT_H_ODDERIKF

namespace my {

    template<typename I>
    void insertsort(I low, I high);

    template<typename L>
    bool verify(L &list);

    template<typename I>
    void quickinsertsort(I low, I high);

    template<typename I>
    void quicksort(I low, I high);

    template<typename I>
    void doublepivotquicksort(I low, I high);


#include "sort_impl.hpp"

}


#endif