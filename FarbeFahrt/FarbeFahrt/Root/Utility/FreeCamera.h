# pragma once

# include "Vector3.h"

/// <summary>���R�ȃJ�����ړ����T�|�[�g����J�����N���X</summary>
class FreeCamera
{
public:

	FreeCamera();

public:

	/// <summary>�J�����̍��W���w�肷��</summary>
	/// <param name="position">���W</param>
	void setPosition(const Vector3& position);

	/// <summary>�J�����̕������w�肷��</summary>
	/// <param name="direction">����</param>
	void setDirection(const Vector3& direction);

	/// <summary>�J�������ړ�������</summary>
	/// <param name="translation">�ړ���</param>
	void move(const Vector3& translation);

	/// <summary>�J��������]������</summary>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	void rotate(const Vector3& axis, double angle);

	/// <summary>�J�����Ɏw����W����������</summary>
	/// <param name="target">�����_</param>
	void lookAt(const Vector3& target);

	/// <summary>�ݒ�𔽉f����</summary>
	void apply() const;

public:

	/// <summary>�J�������猩���E�����x�N�g����Ԃ�</summary>
	Vector3 right() const;

	/// <summary>�J�������猩��������x�N�g����Ԃ�</summary>
	Vector3 up() const;

	/// <summary>�J�������猩���O�����x�N�g����Ԃ�</summary>
	Vector3 forward() const;

private:

	Vector3 m_position;

	Vector3 m_direction;
};
