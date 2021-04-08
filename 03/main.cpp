#include <iostream>
#include <cassert>
#include "matrix.hpp"

std::ostream& operator<< (std::ostream &out, const Matrix &matrix) {
    size_t m = matrix.getRowSize(), n = matrix.getColumnSize();

    for(size_t i = 0; i < m; ++i, out << std::endl)
            for(size_t j = 0; j < n; ++j)
                out << matrix.getValue(i, j) << " ";

    return out;
}

bool operator== (const Matrix &matrix1, const Matrix &matrix2){
    size_t m = matrix1.getRowSize(), n = matrix1.getColumnSize();

    if(m != matrix2.getRowSize() || n != matrix2.getColumnSize())
        return false;

    bool f = true;

    for(size_t i = 0; f && i < m; ++i)
        for(size_t j = 0; f && j < n; ++j)
            f = matrix1.getValue(i, j) == matrix2.getValue(i, j);

    return f;
}

bool operator!= (const Matrix &matrix1, const Matrix &matrix2){
    return !(matrix1 == matrix2);
}

Matrix operator+(const Matrix &matrix1, const Matrix &matrix2){
    size_t m = matrix1.getRowSize(), n = matrix1.getColumnSize();

    if(m != matrix2.getRowSize() || n != matrix2.getColumnSize())
        throw std::out_of_range("");

    Matrix ans(m, n);

    for(size_t i = 0; i < m; ++i)
        for(size_t j = 0; j < n; ++j)
            ans[i][j] = matrix1.getValue(i, j) + matrix2.getValue(i, j);

    return ans;
}

void StandartTest(){
	Matrix m(3, 3);
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			m[i][j] = 3*i + j;

	assert(m.getRowSize() == 3 && m.getColumnSize() == 3);
	assert(m[1][1] == 4);
	
	m *= 3;
	
	//std::cout << m << std::endl; //for cout test
	
	assert(m[1][1] = 12);

	Matrix I(3, 3);
	for(int i = 0; i < 3; ++i)
		I[i][i] = 1;

	Matrix ans = I + m;
	assert(I != ans);
	assert(ans[0][0] == 1);	
}

void BooleanTest(){
	Matrix m1(3, 3), m2(3, 4), m3(3, 3), m4(3, 3);

	m1[0][0] = 1;

	assert(m1 != m2);
	assert(m1 != m3);
	assert(m3 == m4);
}

void OutRangeTest(){
	Matrix m(3, 3);
	bool f = false;
	
	try {
		m[100][5] = 1000;
	}
	catch(std::out_of_range const&){
		f = true;
	}
	
	assert(f);
}

int main(){
	
	StandartTest();
	BooleanTest();	
	OutRangeTest();	

	return 0;
}
//Матрица заполняется по умолчанию нулями для удобства
