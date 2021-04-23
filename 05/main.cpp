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
    uint64_t d;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c, d);
    }
};


void StandartTest(){
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void BigTest(){
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataBig y { 0, false, 0, 10};

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::VariableBig);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void InvalidTest(){
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataInvalid y { 0, false, 0, 10};

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::DiffrentType);

    assert(x.a == y.a);
    assert(x.b == y.b);
}

void InvalidTest2(){
    DataInvalid x { 1, true, 2, 0};

    std::stringstream stream;

    Serializer serializer(stream);
    const Error err = serializer.save(x);

    assert(err == Error::CorruptedArchive);
}


int main() {

    StandartTest();
    BigTest();
    InvalidTest();
    InvalidTest2();

    return 0;
}