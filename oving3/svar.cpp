#include "../mylib/timeit.hpp"
#include "../mylib/sort.hpp"
#include <random>



template <typename L>
void printl(L& l){
    std::cout << "[" << *std::begin(l);
    for( auto i = std::begin(l)+1 ; i < std::end(l); i++) std::cout << ", " << *i ;
    std::cout << "]" << std::endl;
}

int main() {
    using namespace my;
    std::random_device device;
    std::mt19937_64 mers {device()};
    std::uniform_int_distribution<uint64_t> dist {1, UINT64_MAX};

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
    for (uint64_t len = 1 << 5; len < 1 << 22; len += len >> 4){
        std::vector<uint64_t> l_def_1piv(len);
        std::generate( std::begin(l_def_1piv), std::end(l_def_1piv), gen);
        std::vector<uint64_t> l_def_2piv(l_def_1piv);
        std::vector<uint64_t> l_def_ipiv(l_def_1piv);

        std::vector<uint64_t> l_dob_1piv(len);
        std::generate( std::begin(l_dob_1piv), std::end(l_dob_1piv), gen2);
        std::vector<uint64_t> l_dob_2piv(l_dob_1piv);
        std::vector<uint64_t> l_dob_ipiv(l_dob_1piv);


        long double t_def_1piv = my::timeit(quicksort<std::vector<uint64_t>::iterator>, std::begin(l_def_1piv), std::end(l_def_1piv));
        assert(verify(l_def_1piv));
        long double t_def_2piv = my::timeit(doublepivotquicksort<std::vector<uint64_t>::iterator>, std::begin(l_def_2piv), std::end(l_def_2piv));
        assert(verify(l_def_2piv));
        long double t_def_ipiv = my::timeit(doublepivotquicksort<std::vector<uint64_t>::iterator>, std::begin(l_def_ipiv), std::end(l_def_ipiv));
        assert(verify(l_def_ipiv));
        
        long double t_dob_1piv = my::timeit(quicksort<std::vector<uint64_t>::iterator>, std::begin(l_dob_1piv), std::end(l_dob_1piv));
        assert(verify(l_dob_1piv));
        long double t_dob_2piv = my::timeit(doublepivotquicksort<std::vector<uint64_t>::iterator>, std::begin(l_dob_2piv), std::end(l_dob_2piv));
        assert(verify(l_dob_2piv));
        long double t_dob_ipiv = my::timeit(doublepivotquicksort<std::vector<uint64_t>::iterator>, std::begin(l_dob_ipiv), std::end(l_dob_ipiv));
        assert(verify(l_dob_ipiv));
        
        long double t_sor_1piv = my::timeit(quicksort<std::vector<uint64_t>::iterator>, std::begin(l_dob_1piv), std::end(l_dob_1piv));
        assert(verify(l_dob_1piv));
        long double t_sor_2piv = my::timeit(doublepivotquicksort<std::vector<uint64_t>::iterator>, std::begin(l_dob_2piv), std::end(l_dob_2piv));
        assert(verify(l_dob_2piv));
        long double t_sor_ipiv = my::timeit(doublepivotquicksort<std::vector<uint64_t>::iterator>, std::begin(l_dob_ipiv), std::end(l_dob_ipiv));
        assert(verify(l_dob_ipiv));
        

        std::cout << len << " " << t_def_1piv << " " << t_def_2piv << " " << t_def_ipiv << " " << t_dob_1piv << " " << t_dob_2piv << " " << t_dob_ipiv << " " << t_sor_1piv << " " << t_sor_2piv << " " << t_sor_ipiv;
        std::cout << std::endl;

    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
