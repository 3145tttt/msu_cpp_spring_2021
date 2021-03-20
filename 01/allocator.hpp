#pragma once

#include <cstddef>

class Allocator 
{
private:
    size_t maxAllocSize = 0;
	size_t offset = 0;
	char* ptr = nullptr;
public:
	void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
	size_t getOffset();
	~Allocator();
};
