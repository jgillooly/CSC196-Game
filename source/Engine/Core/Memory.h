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
		/*void add(void* address, size_t size);
		void remove(void* address);*/
	private:

	};
}