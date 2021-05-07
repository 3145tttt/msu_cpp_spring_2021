#include <iostream>
#include <cassert>
#include "vector.hpp"

void StandartTest(){
    Vector<int> a(3, 2);
    a.push_back(10);
    a.reserve(10);
    
    assert(a[0] == 2);
    assert(a[1] == 2);
    assert(a[2] == 2);
    assert(a[3] == 10);
    assert(a.size() == 4);
    assert(a.capacity() == 10);
    a[2] = 12;
    assert(a[2] == 12);
    a.pop_back();
    assert(a.size() == 3);
    assert(a.capacity() == 10);

    assert(a.end() - a.begin() == a.size());

    auto i = a.begin();
    assert(*i == 2);
    ++i;
    assert(*i == 2);
    ++i;
    assert(*i == 12);
    ++i;
    assert(i == a.end());

    i = a.begin();
    int t = i[2];
    assert(t == 12);

    auto i2 = a.rbegin();
    assert(*i2 == 12);
    ++i2;
    assert(*i2 == 2);
    ++i2;
    assert(*i2 == 2);
    ++i2;
    assert(i2 == a.rend());
}

void IOTest(){
    Vector<int> a;
    assert(a.empty() == 1);
    assert(a.capacity() == 1);
    for(int i = 0; i < 1000; ++i){
        a.push_back(i*i);
    }
    assert(a.capacity() == 1024);
    assert(a.size() == 1000);
    for(int i = 0; i < a.size(); ++i){
        assert(a[i] == i*i);
    }
    int j = 0;
    for(auto i = a.begin(); i < a.end(); ++i){
        assert(*i == j*j);
        ++j;
    }
}

int main(){

    StandartTest();
    IOTest();
    return 0;
}