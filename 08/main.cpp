#include <iostream>
#include "pool.hpp"

struct A{
    int value = 1000;
};

int func(A& t){
    return t.value;
}

int main(){
    ThreadPool pool(8);

    auto task1 = pool.exec(func, A());
    task1.get();

    auto task2 = pool.exec([]() { return 1; });
    task2.get();
    std::cout << "OK" << std::endl;
    return 0;
}