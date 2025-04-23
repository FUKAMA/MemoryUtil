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
		// �쐬
		//-----------------------------------

		/// <summary>
		/// ��̃������R���e�i���쐬����
		/// </summary>
		/// <param name="...args"></param>
		ResizableMemoryContainer(AllocArgTypes&&...args)
			:allocator_(args...)
			, memory_(nullptr)
			, capacity_(0)
		{

		}

		//-----------------------------------
		// ���
		//-----------------------------------

		/// <summary>
		/// �قȂ�A���P�[�^���g�p���Ă���R���e�i���m�ő�����s��
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
		/// �����^�̃A���P�[�^���g�p���Ă���R���e�i���m�ő�����s��
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
		// �J��
		//-----------------------------------

		~ResizableMemoryContainer()
		{
			allocator_.Deallocate(memory_);
		}

		//-----------------------------------
		// ����������
		//-----------------------------------

		/// <summary>
		/// �������T�C�Y��ύX����
		/// �ύX��̂ق����������T�C�Y���������ꍇ�͈ꕔ�f�[�^���؂�̂Ă���
		/// </summary>
		/// <param name="capacity"></param>
		void Resize(const size_t afterCapacity)
		{
			const size_t beforeCapacity = capacity_;

			// �������T�C�Y�̕ύX�̕K�v���Ȃ���Ή������Ȃ�
			if (beforeCapacity == afterCapacity)
			{
				return;
			}

			// �ύX��Ɏg�p���郁�������m�ۂ���
			void* newMemory = allocator_.Allocate(afterCapacity);

			// ���������ړ�����ʂ����߂�
			size_t copyMemSize = beforeCapacity;
			if (copyMemSize > afterCapacity)
			{
				copyMemSize = afterCapacity;
			}


			if (afterCapacity > 0 && beforeCapacity > 0)
			{
				// ���������ړ�����
				memcpy(newMemory, memory_, copyMemSize);
			}

			allocator_.Deallocate(memory_);

			memory_ = newMemory;
			capacity_ = afterCapacity;
		}

		//-----------------------------------
		// �擾
		//-----------------------------------

		/// <summary>
		/// �m�ۂ����������̐擪�A�h���X���擾
		/// </summary>
		/// <returns></returns>
		void* Data()const
		{
			return memory_;
		}

		/// <summary>
		/// �e�ʂ�Ԃ�
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
