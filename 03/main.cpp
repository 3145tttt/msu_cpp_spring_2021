#include <iostream>
#include <cassert>
#include "matrix.hpp"

void StandartTest(){
	Matrix m(3, 3);
	for(size_t i = 0; i < 3; ++i)
		for(size_t j = 0; j < 3; ++j)
			m[i][j] = 3*i + j;

	assert(m.getRowSize() == 3 && m.getColumnSize() == 3);
	for(size_t i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			assert(m[i][j] == 3*i + j);
	
	m *= 3;
	
	for(size_t i = 0; i < 3; ++i)
		for(size_t j = 0; j < 3; ++j)
			assert(m[i][j] == 9*i + 3*j);
	Matrix I(3, 3);
	for(size_t i = 0; i < 3; ++i)
		I[i][i] = 1;

	Matrix ans = I + m;
	assert(I != ans);
	for(size_t i = 0; i < 3; ++i)
		for(size_t j = 0; j < 3; ++j)
			assert(ans[i][j] == (9*i + 3*j + (i == j)));
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

void Test1(){
	Matrix m(1, 1);
	m[0][0] = 100;
	assert(m.getValue(0, 0) == 100);
	m *= 100;
	assert(m.getValue(0, 0) == 10000);
}

void coutTest(){
	Matrix m(3, 3);
	for(size_t i = 0; i < 3; ++i)
		for(size_t j = 0; j < 3; ++j)
			m[i][j] = i + j;
	m *= 10;
	std::cout << "this is my <<" << std::endl;
	std::cout << m;
}

int main(){
	
	StandartTest();
	BooleanTest();	
	OutRangeTest();	
	Test1();
	coutTest();
	return 0;
}

