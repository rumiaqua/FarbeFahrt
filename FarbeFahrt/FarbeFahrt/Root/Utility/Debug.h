# pragma once

# include <Dxlib.h>
# include "String.h"
# include <utility>

/// <summary>�f�o�b�O���</summary>
class Debug
{
private:

	/// <summary>�R���X�g���N�^</summary>
	Debug();

	/// <summary>�R�s�[�R���X�g���N�^�폜</summary>
	Debug(const Debug&) = delete;

	/// <summary>������Z�q�폜</summary>
	Debug& operator = (const Debug&) = delete;

	/// <summary>�P��C���X�^���X��Ԃ�</summary>
	static Debug& Instance();

public:

	/// <summary>��ʂɃf�o�b�O�\������</summary>
	template <typename ...Args>
	inline static void Print(const String& format, Args&& ...args)
	{
		printfDx(format.toNarrow().c_str(), std::forward<Args>(args)...);
	}

	/// <summary>��ʂɃf�o�b�O�\���������Ɖ��s����</summary>
	template <typename ...Args>
	inline static void Println(const String& format, Args&& ...args)
	{
		Print(format.toNarrow().c_str(), std::forward<Args>(args)...);
		printfDx("\n");
	}

	/// <summary>�X�V����</summary>
	static void Update();

	/// <summary>���t���[���N���A���邩�ǂ�����ݒ肷��</summary>
	static void SetClear(bool isClear);

	/// <summary>���t���[���N���A���邩�ǂ�����Ԃ�</summary>
	static bool IsClear();

	/// <summary>�f�o�b�O�\�����N���A����</summary>
	static void Clear();

	/// <summary>���b�Z�[�W�{�b�N�X��\������</summary>
	static void Show(const char* messsage, const char* caption, UINT style);

	/// <summary>�t�H���g�T�C�Y��ύX����</summary>
	static void ChangeFontSize(int fontSize);

private:

	bool m_isClear;

	int m_fontSize;
};
