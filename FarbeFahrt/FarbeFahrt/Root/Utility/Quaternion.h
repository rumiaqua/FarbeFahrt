# pragma once

# include "Vector4.h"
# include "Matrix.h"

namespace Utility
{
	// -------------------------------------------------------------------
	// �O�u�錾
	// -------------------------------------------------------------------

	class Quaternion
	{
		// ---------------------------------------------------------------
		// �V�X�e��
		// ---------------------------------------------------------------

	public:

		Quaternion();

		Quaternion(Quaternion const& q);

		Quaternion(float x, float y, float z, float w);

		// ---------------------------------------------------------------
		// �萔
		// ---------------------------------------------------------------

	public:

		/// <summary>�P�ʃN�H�[�^�j�I����Ԃ�</summary>
		static Quaternion& Identity();

		// ---------------------------------------------------------------
		// �ϊ�����
		// ---------------------------------------------------------------

	public:

		/// <summary>�C�ӎ���]���s�Ȃ�</summary>
		Quaternion& Rotate(Vector3 const& axis, float angle);

		/// <summary>���[����]���s�Ȃ�</summary>
		Quaternion& Roll(float angle);

		/// <summary>�s�b�`��]���s�Ȃ�</summary>
		Quaternion& Pitch(float angle);

		/// <summary>���[��]���s�Ȃ�</summary>
		Quaternion& Yaw(float angle);

		/// <summary>�s��ɕϊ�����</summary>
		Matrix ToMatrix();

		// ---------------------------------------------------------------
		// �ϊ��N�H�[�^�j�I����Ԃ�
		// ---------------------------------------------------------------

	public:

		/// <summary>�C�ӎ���]�N�H�[�^�j�I����Ԃ�</summary>
		static Quaternion Rotation(Vector3 const& axis, float angle);

		/// <summary>�s��ɕϊ�����</summary>
		static Matrix ToMatrix(Quaternion const& q);

		/// <summary>�����N�H�[�^�j�I����Ԃ�</summary>
		static Quaternion Conjugate(Quaternion const& q);

	public:

		float x, y, z, w;
	};

	// ---------------------------------------------------------------
	// ���Z�q�I�[�o�[���[�h
	// ---------------------------------------------------------------

	Quaternion operator * (Quaternion const& q1, Quaternion const& q2);
	Quaternion& operator *= (Quaternion& q1, Quaternion const& q2);
	Vector3 operator * (Vector3 const& v, Quaternion const& q);
	Vector3& operator *= (Vector3 & v, Quaternion const& q);
}
