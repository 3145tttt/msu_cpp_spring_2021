#include <iostream>
#include <string>
#include <cassert>
#include "format.hpp"


void StandartTest(){
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
}

void NonStandartTest(){
    auto text = format("{1}+{0} = {2}{2}{2}", 2, "one", "I");;
    assert(text == "one+2 = III");
}

void ExeceptionTest1(){
    try{
        auto text = format("{1}+{0} = {2}{2}{3}", 2, "one", "I");;
    }
    catch(const std::runtime_error& e){
        std::string s = e.what();
        assert(s == "Format number very big");
        return;
    }
    assert(false);
}

void ExeceptionTest2(){
    try{
        auto text = format("{1}+{0} = {2}{2}{-2}", 2, "one", "I");;
    }
    catch(const std::runtime_error& e){
        std::string s = e.what();
        assert(s == "Finding character in context isn't number");
        return;
    }
    assert(false);
}

void ExeceptionTest3(){
    try{
        auto text = format("{}+{0} = {2}{2}{2}", 2, "one", "I");;
    }
    catch(const std::runtime_error& e){
        std::string s = e.what();
        assert(s == "{_} must have number");
        return;
    }
    assert(false);
}

void ExeceptionTest4(){
    try{
        auto text = format("}{1}+{0} = {2}{2}{2}", 2, "one", "I");;
    }
    catch(const std::runtime_error& e){
        std::string s = e.what();
        assert(s == "} so much");
        return;
    }
    assert(false);
}

int main(){
    StandartTest();
    NonStandartTest();
    ExeceptionTest1();
    ExeceptionTest2();
    ExeceptionTest3();
    ExeceptionTest4();
    return 0;
}