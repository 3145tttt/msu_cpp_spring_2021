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
    catch(const std::logic_error& e){
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
    catch(const std::logic_error& e){
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
    catch(const std::logic_error& e){
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
    catch(const std::logic_error& e){
        std::string s = e.what();
        assert(s == "} so much");
        return;
    }
    assert(false);
}

void Test1(){
    auto text = format("I love pineapples");
    assert(text == "I love pineapples");
}

void Test2(){
    auto text = format("I love {0}",  "pineapples");
    assert(text == "I love pineapples");
}

void Test3(){
    auto text = format("{0}",  "pineapples");
    assert(text == "pineapples");
}

void Test4(){
    auto text = format("{0}{1}{0}{1}",  "pineapples","+");
    assert(text == "pineapples+pineapples+");
}

void Test5(){
    auto text = format("{0}{1}{2}{3}{4}{5}{6}{7}{8}{9}{10}",  "+", "-", "+", "-", "+", "-", "+", "-", "+", "-", "+");
    assert(text == "+-+-+-+-+-+");
}


int main(){
    StandartTest();
    NonStandartTest();
    ExeceptionTest1();
    ExeceptionTest2();
    ExeceptionTest3();
    ExeceptionTest4();

    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    return 0;
}