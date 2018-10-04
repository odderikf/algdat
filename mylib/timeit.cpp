#include "timeit.hpp"
#include <boost/date_time.hpp>
template <typename F, typename ... Args>
long double my::timeit(F a, Args ... arg){
    using namespace boost::posix_time;
    //int runder = 0;
    long double tid;
    ptime slutt;
    ptime start = microsec_clock::local_time();
    //do{
        a(arg...);
        slutt = microsec_clock::local_time();
        //++runder;
    //}while((slutt-start).total_milliseconds() < 200);
    tid = (slutt-start).total_nanoseconds(); // (long double)(runder);
    return tid;
}
