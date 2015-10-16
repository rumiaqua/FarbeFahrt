# pragma once

# include <array>

# include <DxLib.h>

/// <summary>�}�E�X�N���X</summary>
class Mouse
{
private:

	/// <summary>�f�t�H���g�R���X�g���N�^</summary>
	Mouse();

	/// <summary>�R�s�[�R���X�g���N�^�̍폜</summary>
	Mouse(const Mouse&) = delete;

	/// <summary>������Z�q�̍폜</summary>
	Mouse& operator = (const Mouse&) = delete;

	/// <summary>�ÓI�C���X�^���X��Ԃ�</summary>
	static Mouse& instance();

public:

	/// <summary>�X�V����</summary>
	static void update();

	/// <summary>�}�E�X�̍��W��Ԃ�</summary>
	static POINT position();

	/// <summary>�����ꂽ�u�Ԃ��ǂ�����Ԃ�</summary>
	/// <param name="mouseCode">DxLib�̃}�E�X�R�[�h</param>
	static bool isClicked(int mouseCode);

	/// <summary>������Ă��邩�ǂ�����Ԃ�</summary>
	/// <param name="mouseCode">DxLib�̃}�E�X�R�[�h</param>
	static bool isPressed(int mouseCode);

	/// <summary>�����ꂽ�u�Ԃ��ǂ�����Ԃ�</summary>
	/// <param name="mouseCode">DxLib�̃}�E�X�R�[�h</param>
	static bool isReleased(int mouseCode);

	/// <summary>�z�C�[���̕ω��ʂ�Ԃ�</summary>
	static int scrollValue();

	static VECTOR screenPointToWorld(float z);

private:

	POINT m_position;

	int m_scrollValue;

	int m_previousBuffer;

	int m_currentBuffer;
};
