#include <iostream>
#include <sstream>
#include <cassert>
#include "serializer.hpp"
#include "deserializer.hpp"

struct Data{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c);
    }
};

struct DataBig{
    uint64_t a;
    bool b;
    uint64_t c;
    uint64_t d;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c, d);
    }
};

struct DataInvalid{
    uint64_t a;
    bool b;
    int c;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c);
    }
};


void StandartTest(){
    Data x { 3, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a && x.a == 3);
    assert(x.b == y.b && x.b == true);
    assert(x.c == y.c && x.c == 2);
}

void BigTest(){
    Data x { 10, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataBig y { 0, false, 0, 10};

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::VariableBig);

    assert(x.a == y.a && x.a == 10);
    assert(x.b == y.b && x.b == true);
    assert(x.c == y.c && x.c == 2);
}

void InvalidTest(){
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataInvalid y { 0, false, 0};

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::CorruptedArchive);
}

void InvalidTest2(){
    DataInvalid x { 1, true, 2};

    std::stringstream stream;

    Serializer serializer(stream);
    const Error err = serializer.save(x);

    assert(err == Error::CorruptedArchive);
}

struct DataOnlyBool{
    bool t;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(t);
    }
};

struct DataOnlyInt{
    uint64_t t;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(t);
    }
};

void OnceTests(){
    DataOnlyBool x {true}, y {false};

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.t == y.t && x.t == true);
}

void OnceTestsInt(){
    DataOnlyInt x {123123}, y {1111};

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.t == y.t && x.t == 123123);
}

int main() {

    StandartTest();
    BigTest();
    InvalidTest();
    InvalidTest2();
    OnceTests();
    OnceTestsInt();

    return 0;
}