#pragma once

namespace utl
{
	/// <summary>
	/// �������m�ۂ̎�i��񋟂���C���^�[�t�F�[�X�N���X
	/// ���̃C���^�[�t�F�[�X�Ƀ������A���P�[�^���������Ă��������A
	/// ��{�I�ɃR���X�g���N�^�ɕʂ̃������A���P�[�^��n���ăC���X�^���X���쐬����g������z�肵�Ă���
	/// </summary>
	class IMemoryAllocator
	{
	public:

		/// <summary>
		/// ���������m�ۂ��鏈���̉��z�֐�
		/// �Ԃ����|�C���^������Deallocate�o����K�v������
		/// </summary>
		/// <param name="a_memSize"></param>
		/// <returns></returns>
		virtual void* Allocate(size_t a_memSize) = 0;

		/// <summary>
		/// ���������J�����鏈���̉��z�֐�
		/// </summary>
		/// <param name="memory"></param>
		virtual void Deallocate(void* memory) = 0;

	};
}
