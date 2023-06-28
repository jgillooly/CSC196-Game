#include "Memory.h"
#include <iostream>
void* operator new (size_t size) {
	std::cout << "allocated: " << size << std::endl;
	return malloc(size);
}

void operator delete (void* address, size_t size) {
	std::cout << "deallocated: " << size;

	free(address);
}