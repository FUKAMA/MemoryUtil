#pragma once
#include "../../Allocator/Default/DefaultAllocator.h"
#include <memory.h>

namespace utl
{
	template<typename AllocType = DefaultMemoryAllocator, typename...AllocArgTypes>
	class ResizableMemoryContainer
	{
	public:

		//-----------------------------------
		// 作成
		//-----------------------------------

		/// <summary>
		/// 空のメモリコンテナを作成する
		/// </summary>
		/// <param name="...args"></param>
		ResizableMemoryContainer(AllocArgTypes&&...args)
			:allocator_(args...)
			, memory_(nullptr)
			, capacity_(0)
		{

		}

		//-----------------------------------
		// 代入
		//-----------------------------------

		/// <summary>
		/// 異なるアロケータを使用しているコンテナ同士で代入を行う
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <typeparam name="...TArgTypes"></typeparam>
		/// <param name="src"></param>
		/// <returns></returns>
		template<typename SubAllocType, typename...SubAllocArgTypes>
		ResizableMemoryContainer<AllocType, AllocArgTypes...>& operator=(const ResizableMemoryContainer<SubAllocType, SubAllocArgTypes...>& src)
		{
			const size_t afterCapacity = src.Capacity();

			Resize(0);
			Resize(afterCapacity);

			memcpy(Data(), src.Data(), afterCapacity);

			return *this;
		}

		/// <summary>
		/// 同じ型のアロケータを使用しているコンテナ同士で代入を行う
		/// </summary>
		/// <param name="src"></param>
		/// <returns></returns>
		ResizableMemoryContainer<AllocType, AllocArgTypes...>& operator=(const ResizableMemoryContainer<AllocType, AllocArgTypes...>& src)
		{
			if (this == &src) return *this;

			const size_t afterCapacity = src.Capacity();

			Resize(0);
			Resize(afterCapacity);

			memcpy(Data(), src.Data(), afterCapacity);

			return *this;
		}


		//-----------------------------------
		// 開放
		//-----------------------------------

		~ResizableMemoryContainer()
		{
			allocator_.Deallocate(memory_);
		}

		//-----------------------------------
		// メモリ操作
		//-----------------------------------

		/// <summary>
		/// メモリサイズを変更する
		/// 変更後のほうがメモリサイズが小さい場合は一部データが切り捨てられる
		/// </summary>
		/// <param name="capacity"></param>
		void Resize(const size_t afterCapacity)
		{
			const size_t beforeCapacity = capacity_;

			// メモリサイズの変更の必要がなければ何もしない
			if (beforeCapacity == afterCapacity)
			{
				return;
			}

			// 変更後に使用するメモリを確保する
			void* newMemory = allocator_.Allocate(afterCapacity);

			// メモリを移動する量を求める
			size_t copyMemSize = beforeCapacity;
			if (copyMemSize > afterCapacity)
			{
				copyMemSize = afterCapacity;
			}


			if (afterCapacity > 0 && beforeCapacity > 0)
			{
				// メモリを移動する
				memcpy(newMemory, memory_, copyMemSize);
			}

			allocator_.Deallocate(memory_);

			memory_ = newMemory;
			capacity_ = afterCapacity;
		}

		//-----------------------------------
		// 取得
		//-----------------------------------

		/// <summary>
		/// 確保したメモリの先頭アドレスを取得
		/// </summary>
		/// <returns></returns>
		void* Data()const
		{
			return memory_;
		}

		/// <summary>
		/// 容量を返す
		/// </summary>
		/// <returns></returns>
		size_t Capacity()const
		{
			return capacity_;
		}

	private:

		AllocType allocator_;

		void* memory_;

		size_t capacity_;

	};
}
