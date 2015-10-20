# pragma once
#include "Dxlib.h"

// -------------------------------------------------------------------
// �O�u�錾
// -------------------------------------------------------------------
class Vector4;
class Point3;
class String;

/// <summary>�O�����x�N�g��</summary>
class Vector3
{
public:

	/// <summary>(0, 0, 0)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector3& zero();

	/// <summary>(1, 1, 1)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector3& one();

	/// <summary>(-1, 0, 0)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector3& left();

	/// <summary>(1, 0, 0)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector3& right();

	/// <summary>(0, 1, 0)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector3& up();

	/// <summary>(0, -1, 0)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector3& down();

	/// <summary>(0, 0, 1)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector3& forward();

	/// <summary>(0, 0, -1)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector3& backward();

public:

	/// <summary>�R���X�g���N�^</summary>
	Vector3();

	/// <summary>�R�s�[�R���X�g���N�^</summary>
	Vector3(const Vector3& v);

	/// <summary>�v�f���w�肵�č\�z����</summary>
	Vector3(float x, float y, float z);

	/// <summary>�l�����x�N�g������\�z����</summary>
	explicit Vector3(const Vector4& v);

	/// <summary>�O�����_����\�z����</summary>
	explicit Vector3(const Point3& v);

	/// <summary>DxLib�̃x�N�g������\�z����</summary>
	explicit Vector3(const VECTOR& v);

	/// <summary>������Z�q</summary>
	Vector3& operator = (const Vector3& v);

public:

	/// <summary>�z��ɕϊ�����</summary>
	operator float* ();

	/// <summary>�z��ɕϊ�����</summary>
	operator const float* () const;

	operator DxLib::VECTOR& ();

	operator const DxLib::VECTOR&() const;

public:

	/// <summary>������ɕϊ����ĕԂ�</summary>
	String toString() const;

	/// <summary>���ς�Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	float dot(const Vector3& v) const;

	/// <summary>�O�ς�Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	Vector3 cross(const Vector3& v) const;

	/// <summary>�����̓���Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	float lengthSquared() const;

	/// <summary>������Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	float length() const;

	/// <summary>���K������</summary>
	Vector3& normalize();

	/// <summary>�C�ӎ��ŉ�]����</summary>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	Vector3& rotate(const Vector3& axis, float angle);

	/// <summary>�x�N�g���Ɏˉe����</summary>
	/// <param name="v">�Ώۂ̃x�N�g��</param>
	Vector3& projection(const Vector3& v);

	/// <summary>�x�N�g���̂Ȃ��p��Ԃ�</summary>
	float angle(const Vector3& v) const;

public:

	/// <summary>������ɕϊ����ĕԂ�</summary>
	/// <param name="v">�x�N�g��</param>
	static String toString(const Vector3& v);

	/// <summary>���ς�Ԃ�</summary>
	/// <param name="v1">�x�N�g��</param>
	/// <param name="v2">�x�N�g��</param>
	static float dot(const Vector3& v1, const Vector3& v2);

	/// <summary>�O�ς�Ԃ�</summary>
	static Vector3 cross(const Vector3& v1, const Vector3& v2);

	/// <summary>�����̓���Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	static float lengthSquared(const Vector3& v);

	/// <summary>������Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	static float length(const Vector3& v);

	/// <summary>���K�������x�N�g����Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	static Vector3 normalize(const Vector3& v);

	/// <summary>�C�ӎ��ŉ�]�����x�N�g���Ԃ�</summary>
	/// <param name="point">�C�ӓ_</param>
	/// <param name="axis">��]��</param>
	/// <param name="angle">��]��</param>
	static Vector3 rotate(const Vector3& point, const Vector3& axis, float angle);

	/// <summary>���e�����x�N�g����Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	/// <param name="target">�Ώۂ̃x�N�g��</param>
	static Vector3 projection(const Vector3& v, const Vector3& target);

	/// <summary>���`��Ԃ����x�N�g����Ԃ�</summary>
	/// <param name="start">�J�n�x�N�g��</param>
	/// <param name="end">�I���x�N�g��</param>
	/// <param name="t">�J�ڗ�</param>
	static Vector3 lerp(const Vector3& start, const Vector3& end, float t);

	/// <summary>�x�N�g���̂Ȃ��p��Ԃ�</summary>
	static float angle(const Vector3& v1, const Vector3& v2);

	/// <summary>���ʐ��`��Ԃ����x�N�g����Ԃ�</summary>
	/// <param name="start">�J�n�x�N�g��</param>
	/// <param name="end">�I���x�N�g��</param>
	/// <param name="t">�J�ڗ�</param>
	static Vector3 slerp(const Vector3& start, const Vector3& end, float t);

public:

	union
	{
		float elm[3];

		float mat[1][3];

		struct
		{
			float r, g, b;
		};

		struct
		{
			float x, y, z;
		};
	};
};

bool operator == (const Vector3& v1, const Vector3& v2);

bool operator != (const Vector3& v1, const Vector3& v2);

Vector3 operator + (const Vector3& v);

Vector3 operator - (const Vector3& v);

Vector3& operator += (Vector3& v1, const Vector3& v2);

Vector3& operator -= (Vector3& v1, const Vector3& v2);

Vector3& operator *= (Vector3& v1, const Vector3& v2);

Vector3& operator *= (Vector3& v, float s);

Vector3& operator /= (Vector3& v1, const Vector3& v2);

Vector3& operator /= (Vector3& v, float s);

Vector3 operator + (const Vector3& v1, const Vector3& v2);

Vector3 operator - (const Vector3& v1, const Vector3& v2);

Vector3 operator * (const Vector3& v1, const Vector3& v2);

Vector3 operator * (const Vector3& v, float s);

Vector3 operator * (float s, const Vector3& v);

Vector3 operator / (const Vector3& v1, const Vector3& v2);

Vector3 operator / (const Vector3& v, float s);
