#pragma once

namespace utl
{
	/// <summary>
	/// メモリ確保の手段を提供するインターフェースクラス
	/// このインターフェースにメモリアロケータを実装してもいいが、
	/// 基本的にコンストラクタに別のメモリアロケータを渡してインスタンスを作成する使い方を想定している
	/// </summary>
	class IMemoryAllocator
	{
	public:

		/// <summary>
		/// メモリを確保する処理の仮想関数
		/// 返したポインタだけでDeallocate出来る必要がある
		/// </summary>
		/// <param name="a_memSize"></param>
		/// <returns></returns>
		virtual void* Allocate(size_t a_memSize) = 0;

		/// <summary>
		/// メモリを開放する処理の仮想関数
		/// </summary>
		/// <param name="memory"></param>
		virtual void Deallocate(void* memory) = 0;

	};
}
