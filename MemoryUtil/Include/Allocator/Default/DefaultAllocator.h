#pragma once
#include "../IMemoryAllocator.h"

namespace utl
{
	/// <summary>
	/// �������A���P�[�^�̎������w�肳��Ȃ��������Ɏg�p���邱�Ƃ�z�肵���N���X
	/// </summary>
	class DefaultMemoryAllocator :public IMemoryAllocator
	{
	public:

		/// <summary>
		/// malloc�Ń��������m�ۂ���
		/// </summary>
		/// <param name="a_memSize"></param>
		/// <returns></returns>
		virtual void* Allocate(size_t memSize)override final;

		/// <summary>
		/// delete�Ń��������J������
		/// </summary>
		/// <param name="memory"></param>
		virtual void Deallocate(void* memory)override final;

	};
}
