#ifndef TIMEIT_H_ODDERIKF
#define TIMEIT_H_ODDERIKF

#include <boost/date_time.hpp>
namespace my{
template <typename F, typename ... Args>
long double timeit(F a, Args ... arg);

#include "timeit_impl.hpp"
}

#endif
