#include "MemoryUtil.h"
#include <malloc.h>

class DefaultMemoryAllocator2 :public utl::IMemoryAllocator
{
public:

	/// <summary>
	/// malloc�Ń��������m�ۂ���
	/// </summary>
	/// <param name="a_memSize"></param>
	/// <returns></returns>
	virtual void* Allocate(size_t memSize)override final
	{
		return malloc(memSize);
	}

	/// <summary>
	/// delete�Ń��������J������
	/// </summary>
	/// <param name="memory"></param>
	virtual void Deallocate(void* memory)override final
	{
		delete memory;
	}


};
int main()
{
	utl::ResizableMemoryContainer container1;
	utl::ResizableMemoryContainer container2;
	utl::ResizableMemoryContainer<DefaultMemoryAllocator2> container3;

	container1.Resize(100);
	container1.Resize(1000);

	container2.Resize(1200);
	container2.Resize(12000);

	container3.Resize(31200);
	container3.Resize(312000);

	container2 = container1;

	container2 = container3;

	return 0;
}