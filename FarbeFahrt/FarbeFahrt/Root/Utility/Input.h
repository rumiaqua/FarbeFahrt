// -----------------------------------------------------------
// �쐬�ҁF�x
// -----------------------------------------------------------
# pragma once

# include <array>

/// <summary>���̓N���X</summary>

class Input
{
private:

	/// <summary>�R���X�g���N�^</summary>
	Input();

	/// <summary>�R�s�[�R���X�g���N�^�̍폜</summary>
	Input(const Input&) = delete;

	/// <summary>�R�s�[���Z�q�̍폜</summary>
	Input& operator = (const Input&) = delete;

private:

	/// <summary>�P��̃C���X�^���X��Ԃ�</summary>
	static Input& instance();

public:

	/// <summary>�L�[���̍X�V</summary>
	static void update();

	/// <summary>�������u�Ԃ��ǂ�����Ԃ�</summary>
	/// <param name="keyCode">DxLib�̃L�[�R�[�h</param>
	static bool isClicked(int keyCode);

	/// <summary>������Ă��邩�ǂ�����Ԃ�</summary>
	/// <param name="keyCode">DxLib�̃L�[�R�[�h</param>
	static bool isPressed(int keyCode);

	/// <summary>�������u�Ԃ��ǂ�����Ԃ�</summary>
	/// <param name="keyCode">DxLib�̃L�[�R�[�h</param>
	static bool isReleased(int keyCode);

private:

	/// <summary>1�t���[���O�̓��͏��</summary>
	std::array<char, 256> m_previousBuffer;

	/// <summary>���݂̓��͏��</summary>
	std::array<char, 256> m_currentBuffer;
};