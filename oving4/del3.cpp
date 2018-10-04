#include <random>
#include "../mylib/timeit.hpp"
#include "../mylib/sort.hpp"
#include "../mylib/heap.hpp"

int main() {
    std::random_device device;
    std::mt19937_64 mers {device()};
    std::uniform_int_distribution<uint64_t> dist {1, 50};//UINT64_MAX};

    bool secondVal = false;
    uint64_t last = 1;

    auto gen = [&dist, &mers](){
        return dist(mers);
    };

    auto gen2 = [&dist, &mers, &secondVal, &last]{
        if (secondVal){
            secondVal = false;
            return last;
        }else{
            secondVal = true;
            return last = dist(mers);
        }
    };
    for (uint64_t len = 1 << 5; len < 1 << 27; len += len >> 4){
        std::vector<uint64_t> l_def_quick(len);
        std::generate( std::begin(l_def_quick), std::end(l_def_quick), gen);
        std::vector<uint64_t> l_def_heap(l_def_quick);

        std::vector<uint64_t> l_dob_quick(len);
        std::generate( std::begin(l_dob_quick), std::end(l_dob_quick), gen2);
        std::vector<uint64_t> l_dob_heap(l_dob_quick);

        long double t_def_quick = my::timeit(my::quicksort<std::vector<uint64_t>::iterator>, std::begin(l_def_quick), std::end(l_def_quick));
        assert(my::verify(l_def_quick));
        long double t_def_heap = my::timeit(my::heapsort<uint64_t>, &l_def_heap);
        assert(my::verify(l_def_heap));

        long double t_dob_quick = my::timeit(my::quicksort<std::vector<uint64_t>::iterator>, std::begin(l_dob_quick), std::end(l_dob_quick));
        assert(my::verify(l_dob_quick));
        long double t_dob_heap = my::timeit(my::heapsort<uint64_t>, &l_dob_heap);
        assert(my::verify(l_dob_heap));

        long double t_sor_quick = my::timeit(my::quicksort<std::vector<uint64_t>::iterator>, std::begin(l_dob_quick), std::end(l_dob_quick));
        assert(my::verify(l_dob_quick));
        long double t_sor_heap = my::timeit(my::heapsort<uint64_t>, &l_dob_heap);
        assert(my::verify(l_dob_heap));

        std::cout << len << " " << t_def_quick << " " << t_def_heap << " " << t_dob_quick << " " << t_dob_heap << " " << t_sor_quick << " " << t_sor_heap;
        std::cout << std::endl;

    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}