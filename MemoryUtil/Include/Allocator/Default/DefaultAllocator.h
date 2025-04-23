#pragma once
#include "../IMemoryAllocator.h"

namespace utl
{
	/// <summary>
	/// メモリアロケータの実装を指定されなかった時に使用することを想定したクラス
	/// </summary>
	class DefaultMemoryAllocator :public IMemoryAllocator
	{
	public:

		/// <summary>
		/// mallocでメモリを確保する
		/// </summary>
		/// <param name="a_memSize"></param>
		/// <returns></returns>
		virtual void* Allocate(size_t memSize)override final;

		/// <summary>
		/// deleteでメモリを開放する
		/// </summary>
		/// <param name="memory"></param>
		virtual void Deallocate(void* memory)override final;

	};
}
