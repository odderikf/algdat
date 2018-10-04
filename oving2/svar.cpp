#include <math.h>
#include <iostream>
#include <vector>

#include "../mylib/timeit.hpp"

long double f(const long double& x, const unsigned long long& n){ //Theta(n)
	if (n)
		return x*f(x,n-1); // Theta(n)
	else
		return 1; // Theta(1)
}

long double g(const long double& x, const unsigned long long& n){ 
//T(n) = aT(n/b) + cn^k
//T(n) = 1T(n/2) + cn^0
//b^k = 2^0 = 1
//a = 0
// a = b => T(n) € = Theta(n^0 log(n)) = Theta( log(n) )
//Theta(log_2(n)) da en dobling i n gir +1 i tid
	if (~n)
		return 1; //Theta(1)
	else if (n%2) //oddetall
		return x* g( x*x , (n-1)/2); //Theta(1), eller theta(g( (n-1)/2  )
	else
		return g( x*x, n/2 ); // Theta(1), eller theta(g(  (n-1)/2  )
} //i testing ser denne derimot statisk ut :?
// i testing i python så var begge metoder eksponensiell :/, mest sannsynlig pga overhead. Hadde også merkbare hopp ved toer-eksponentene

long double n(const long double& x, const unsigned long long& n){
	return pow(x, (long double)n);
}

int main(){
    std::cout.sync_with_stdio(false);
    const long double x = 1.10000111111;
    std::vector<unsigned long long> xs;
    std::vector<unsigned long long> fs1;
    std::vector<unsigned long long> gs1;
    std::vector<unsigned long long> ns1;
    std::vector<unsigned long long> fs2;
    std::vector<unsigned long long> gs2;
    std::vector<unsigned long long> ns2;
    unsigned long long fstart = 1;
    unsigned long long flimit = 50; 
    unsigned long long fstep = 1;
    unsigned long long gstart = 1;
    unsigned long long glimit = 50; 
    unsigned long long gstep = 1;
    for(unsigned long long i=fstart; i<flimit; i += fstep){
        std::cout << i << " "
                  << my::timeit(f,x,i) << " "
                  << my::timeit(n,x,i) << std::endl;
    }
    std::cout << "DONE" << std::endl;
    for(unsigned long long i=gstart; i<glimit; i += gstep){
        std::cout << i << " "
                  << my::timeit(g,x,i) << " "
                  << my::timeit(n,x,i) << std::endl;
    }
    std::cout << std::endl;


    return EXIT_SUCCESS;
}
