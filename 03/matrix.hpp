#pragma once
#include <iostream>

class Matrix {

    class ProxyRow {
    private:
        int32_t *data_;
        size_t columnSize;
    public:

        void setDataSize(size_t n);

        int32_t& operator[](size_t j);

        ~ProxyRow();
    };

public:

    Matrix(size_t m, size_t n);

    size_t getRowSize() const;

    size_t getColumnSize() const;

    void operator*=(int32_t c);

    ProxyRow& operator[](size_t i);

    int32_t getValue(size_t i, size_t j) const;

    ~Matrix();


private:
    ProxyRow *rows_;
    size_t rowSize, columnSize;

};
