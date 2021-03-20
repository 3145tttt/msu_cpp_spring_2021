#include <iostream>
#include "allocator.hpp"
#include <cassert>


void DefualtTest(){
	Allocator myAllocator;
	myAllocator.makeAllocator(100);
	char* ptr = myAllocator.alloc(20);
	assert(myAllocator.getOffset() == 20);
}

void LimitTest(){
    Allocator myAllocator;
    myAllocator.makeAllocator(100);
    char* ptr = myAllocator.alloc(100);
    assert(myAllocator.getOffset() == 100);
}

void RepeatTest(){
    Allocator myAllocator;
    myAllocator.makeAllocator(100);
    char* ptr = myAllocator.alloc(20);
	ptr = myAllocator.alloc(40);
	assert(myAllocator.getOffset() == 60);
}

void OverflowTest(){
    Allocator myAllocator;
	myAllocator.makeAllocator(100);
	char* ptr = myAllocator.alloc(20);
	ptr = myAllocator.alloc(90);
	assert(ptr == nullptr);
	assert(myAllocator.getOffset() == 20);
}

void ResetTest(){
	Allocator myAllocator;
    myAllocator.makeAllocator(100);
	char* ptr = myAllocator.alloc(30);
	ptr = myAllocator.alloc(90);
	myAllocator.reset();
	ptr = myAllocator.alloc(90);
	assert(myAllocator.getOffset() == 90);
}

void ResizeTest(){
	Allocator myAllocator;
	myAllocator.makeAllocator(100);
	char* ptr = myAllocator.alloc(110);
	myAllocator.makeAllocator(160);
	ptr = myAllocator.alloc(110);
	assert(myAllocator.getOffset() == 110);
	assert(ptr != nullptr);
}

int main(){
	DefualtTest();
	LimitTest();
	RepeatTest();
	OverflowTest();
	ResetTest();	
	ResizeTest();	

	std::cout << "Success!" << std::endl;
	return 0;
}
