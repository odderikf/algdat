#include <iostream>
#include <boost/date_time.hpp>
#include "../mylib/timeit.cpp"

std::vector<long> nsquared(std::vector<double>& changes){
    double value = 0; //{
    double direction = 0;
    long buyday = -1;
    long sellday = -1;
    double best = -DBL_MAX;
    std::vector<double> values;
    values.emplace_back(value); //} = θ(1)
    for (auto dx : changes){ // løkke = θ(n)
        value += dx;
        values.emplace_back(value); // innhold = θ(1)
    } //1*n = n
    //+
    for (auto i = values.begin(); i<values.end(); ++i){ // løkke = θ(n)
        for (auto j = i+1; j<values.end(); j++){ //sum 1 to n-1 = θ(n²)
            if (*j - *i > best){
                best = *j - *i;
                buyday = i-values.begin();
                sellday = j-values.begin(); //innhold = θ(1)
            }
        }
    } //n²*1 = n²
    return {buyday, sellday, (long)best};

}

std::vector<long> nlinear(std::vector<double>& changes){
    double lowest = 0;
    long lowestDay = 0;
    double highest = 0;
    long highestDay = 0;
    double value = 0;
    std::vector<long> bestHigh; //low high == buy sell
    std::vector<long> bestLow; //low high == buy sell
    std::vector<double> values; //deklareringer er θ(1)

    for(auto dx = changes.begin(); dx < changes.end(); dx++){ //løkke gjennom liste så θ(n)
        value += *dx;
        if(value < lowest){
            bestHigh.emplace_back(highestDay);
            bestLow.emplace_back(lowestDay);
            values.emplace_back(highest-lowest);
            lowest = highest = value;
            lowestDay = highestDay = dx-changes.begin();
        }
        if(value > highest){
            highest = value;
            highestDay = dx-changes.begin();
        }
        //ifs og emplace etc θ(1)
    } // 1*n=n

    int besti = 0;
    for (int i = 0; i < bestHigh.size(); ++i) { //størrelse på disse er mellom 1 og n, altså omega(1) og O(n)
        if (values[i] > values[besti]){
            besti = i;
        } //lookup er θ(1)
    }
    std::vector<long> results;
    results.emplace_back(bestLow[besti]+1);
    results.emplace_back(bestHigh[besti]+1);
    results.emplace_back(values[besti]); //lookups er θ(1)
    return results; //totalt θ(n)

}

int main(){

    using namespace std;


    /*
    vector<double> referencedata = {-1, +3, -9, +2, +2, -1, +2, -1, -5}; //rett svar: kjøp 3 selg 7 val 5
    for(auto i : nlinear(referencedata)) cout << i << " ";
    cout << endl;
    */ //sjekk svar

    // /*
    for (int i = 1; i<1000000000    ; i++) { //40 datapunkter
        vector<double> row;
        for (int j = 0; j < i*10000000; j++){
            row.emplace_back(rand() - RAND_MAX/2);
        }
        cout << row.size() << ", " << my::timeit(nlinear, row) << endl;
    }
    cout << "DONE" << endl;
    // */timing


    return EXIT_SUCCESS;
}
