# pragma once

# include <array>

# include "Point2.h"
# include "Vector3.h"
#include "Utility/Def.h"

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

private:

	/// <summary>�ÓI�C���X�^���X��Ԃ�</summary>
	static Mouse& Instance();

public:

	/// <summary>�X�V����</summary>
	static void Update();

	/// <summary>�}�E�X�̍��W��Ԃ�</summary>
	static Point2 Position();

	/// <summary>�����ꂽ�u�Ԃ��ǂ�����Ԃ�</summary>
	/// <param name="mouseCode">DxLib�̃}�E�X�R�[�h</param>
	static bool IsClicked(int mouseCode);

	/// <summary>������Ă��邩�ǂ�����Ԃ�</summary>
	/// <param name="mouseCode">DxLib�̃}�E�X�R�[�h</param>
	static bool IsPressed(int mouseCode);

	/// <summary>�����ꂽ�u�Ԃ��ǂ�����Ԃ�</summary>
	/// <param name="mouseCode">DxLib�̃}�E�X�R�[�h</param>
	static bool IsReleased(int mouseCode);

	/// <summary>�z�C�[���̕ω��ʂ�Ԃ�</summary>
	static int ScrollValue();

	static Vector3 ScreenPointToWorld(float z);

private:

	Point2 m_position;

	int m_scrollValue;

	int m_previousBuffer;

	int m_currentBuffer;

	Vector3 m_initPosition;
};
