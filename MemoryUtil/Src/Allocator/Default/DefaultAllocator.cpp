#include "Allocator/Default/DefaultAllocator.h"
#include <memory>
#include <cstdlib>

namespace utl
{

	void* DefaultMemoryAllocator::Allocate(size_t memSize)
	{
		return malloc(memSize);
	}

	void DefaultMemoryAllocator::Deallocate(void* memory)
	{
		delete memory;
	}

}