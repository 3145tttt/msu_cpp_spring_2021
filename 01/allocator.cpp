#include "allocator.hpp"

void Allocator::makeAllocator(size_t maxSize){
    if(ptr)
	delete[] ptr;
    offset = 0;
    ptr = new char[maxSize];
    maxAllocSize = maxSize;
}

char* Allocator::alloc(size_t size){
    if(size + offset > maxAllocSize)
        return nullptr;
    char* t = ptr + offset;
    offset += size;
    return t;
}

void Allocator::reset(){
    offset = 0;
}

size_t Allocator::getOffset(){
     //how make read-only property?
     return offset;
}

Allocator::~Allocator(){
     delete[] ptr;
}
