#include <iostream>
#include <cassert>
#include "bigint.hpp"

void StandartTest(){
    BigInt a("1111111111111111"), b("11");
    BigInt c = a + b;
    assert(c == BigInt("1111111111111122"));
    c = a - b;
    assert(c == BigInt("1111111111111100"));
    c = a*2;
    assert(c == BigInt("2222222222222222"));
    c = b + 11;
    assert(c == BigInt("22"));
    c = a*b;
    assert(c == BigInt("12222222222222221"));
}

void BoolTest(){
    BigInt a("100"), b("105");
    BigInt c = 103;
    assert(c > a && c < b);
    assert(c >= a && c <= b);
    assert(c == 103);
    assert(c != 100);
    c = -c;
    b = -b;
    assert(c < a && c > b);
    assert(c <= a && c >= b);
    assert(c != 103);
}

void NegativeTest(){
    BigInt a = -123, b = 23;
    BigInt c = a + b;
    assert(c == -100);
    c = a - b;
    assert(c == -146);
    b = 121;
    c = a + b;
    assert(c == -2);
    c = a*b;
    assert(c == BigInt(-14883));
    assert(c == BigInt("-14883"));
}

void BigTest(){
    BigInt a("1111111111111111"), b("9999999999");
    BigInt c = a*b*b*2;
    assert(c == BigInt("222222222177777755557777782222222222"));
}

void HomeWorkTest(){
    BigInt a = 1;
    BigInt b("123456789012345678901234567890");
    BigInt c = a * b + 2;
    BigInt d;
    d = std::move(c);
    a = d + b;
    assert(a == BigInt("246913578024691357802469135782"));
}

int main(){
    StandartTest();
    BoolTest();
    NegativeTest();
    BigTest();
    HomeWorkTest();
    return 0;
}