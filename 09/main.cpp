#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cassert>
#include "mergeFileSortThread.hpp"

void test(){
    uint64_t MAX = 10000;
    std::vector <uint64_t> a(MAX);

    std::ofstream out("input1.txt", std::ios::out);

    srand(time(NULL));
    for(uint64_t i = 0; i < MAX; ++i){
        a[i] = rand() % 3000001;
        out << a[i] << ' ';
    }

    out.close();

    std::sort(a.begin(), a.end());

    mergeFileSortThread("input1.txt", "output1.txt");

    std::ifstream in("output1.txt", std::ios::in);


    for(uint64_t i = 0; i < MAX; ++i){
        uint64_t x;
        in >> x;

        assert(a[i] == x);
    }
}


int main(){
    test();
    return 0;
}
