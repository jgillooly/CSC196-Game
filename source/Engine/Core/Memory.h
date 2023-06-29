#pragma once
#include <iostream>
namespace antares {
	struct MemoryAllocation {
		void* address;
		size_t size;
		MemoryAllocation* next;
	};

	class MemoryTracker {
	public:
		void add(void* address, size_t size);
		void remove(void* address, size_t size);

		void displayInfo();

	private:
		size_t _bytesAllocated = 0;
		size_t _numAllocations = 0;
	};
	
	extern antares::MemoryTracker g_memoryTracker;
}

