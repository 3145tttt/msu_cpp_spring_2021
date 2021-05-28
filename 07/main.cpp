#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
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
    assert((size_t)(a.end() - a.begin()) == a.size());

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
    Vector<size_t> a;
    assert(a.empty() == 1);
    assert(a.capacity() == 1);
    for(size_t i = 0; i < 1000; ++i){
        a.push_back(i*i);
    }
    assert(a.capacity() == 1024);
    assert(a.size() == 1000);
    for(size_t i = 0; i < a.size(); ++i){
        assert(a[i] == i*i);
    }
    int j = 0;
    for(auto i = a.begin(); i < a.end(); ++i){
        assert(*i == j*j);
        ++j;
    }
}

void Test1(){
    Vector<int32_t> a(10, 9);
    assert(a.size() == 10);
    a.resize(20);
    assert(a.size() == 20);
}

void Test2(){
    Vector<int32_t> a(10);
    assert(a.size() == 10);
    a.push_back(20);
    assert(a[10] == 20);
    for(auto i = 0; i < 10; ++i)
        assert(a[i] == 0);
}

void Test3(){
    Vector<int32_t> a(10, 9);
    assert(!a.empty());
    a.clear();
    assert(a.empty());
    assert(a.capacity() != 0);
}

void Test4(){
    std::vector<int32_t> a(10);
    Vector<int32_t> b(10);

    int32_t c[10] = {1323, -1, -12, 423, 9, 23, 1, 3, -11,-123};

    for(auto i = 0; i < 10; ++i){
        a[i] = c[i];
        b[i] = a[i];
    }

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    for(auto i = 0; i < 10; ++i)
        assert(a[i] == b[i]);
}

void Test5(){

    struct my_pair{
        int32_t first;
        int32_t second;

        my_pair(int32_t x, int32_t y){
            first = x;
            second = y;
        }
        my_pair(){
            first = 0;
            second = 0;
        }
    };
    

    Vector<my_pair> a;
    a.emplace_back(10, 20);
    a.emplace_back(-20, 10);
    a.emplace_back(3, 22);

    int32_t f[3] = {10, -20, 3};
    int32_t s[3] = {20, 10, 22};

    for (size_t i = 0; i < a.size(); ++i){
        assert(f[i] == a[i].first);
        assert(s[i] == a[i].second);
    }
}

int main(){
    StandartTest();
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    IOTest();
    return 0;
}