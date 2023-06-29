#include "Memory.h"
#include <iostream>
using namespace std;

antares::MemoryTracker antares::g_memoryTracker;

void* operator new (size_t size) {
	void* address = malloc(size);

	antares::g_memoryTracker.add(address, size);

	return address;
}

void operator delete (void* address, size_t size) {
	antares::g_memoryTracker.remove(address, size);

	free(address);
}

namespace antares {
	void MemoryTracker::add(void* address, size_t size) {
		_bytesAllocated += size;
		_numAllocations++;
	}

	void MemoryTracker::remove(void* address, size_t size) {
		_bytesAllocated -= size;
		_numAllocations--;
	}

	void MemoryTracker::displayInfo() {
		cout << "Current Bytes Allocated: " << _bytesAllocated << endl;
		cout << "Current Allocations: " << _numAllocations << endl;
	}
}

