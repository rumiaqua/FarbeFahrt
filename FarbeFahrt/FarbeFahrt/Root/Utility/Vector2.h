# pragma once

// -------------------------------------------------------------------
// �O�u�錾
// -------------------------------------------------------------------
class Vector3;
class Point2;
class String;

/// <summary>�񎟌��x�N�g��</summary>
class Vector2
{
public:

	/// <summary>(0, 0)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector2& Zero();

	/// <summary>(1, 1)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector2& One();

	/// <summary>(-1, 0)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector2& Left();

	/// <summary>(1, 0)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector2& Right();

	/// <summary>(0, -1)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector2& Up();

	/// <summary>(0, 1)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector2& Down();

public:

	/// <summary>�R���X�g���N�^</summary>
	Vector2();

	/// <summary>�R�s�[�R���X�g���N�^</summary>
	Vector2(const Vector2& v);

	/// <summary>�v�f���w�肵�č\�z����</summary>
	Vector2(float x, float y);

	/// <summary>�O�����x�N�g������\�z����</summary>
	explicit Vector2(const Vector3& v);

	/// <summary>�񎟌��_����\�z����</summary>
	explicit Vector2(const Point2& v);

	/// <summary>������Z�q</summary>
	Vector2& operator = (const Vector2& v);

public:

	/// <summary>�z��ɕϊ�����</summary>
	operator float* ();

	/// <summary>�z��ɕϊ�����</summary>
	operator const float* () const;

public:

	/// <summary>������ɕϊ����ĕԂ�</summary>
	String toString() const;

	/// <summary>���ς�Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	float dot(const Vector2& v) const;

	/// <summary>�O�ς�Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	float cross(const Vector2& v) const;

	/// <summary>�����̓���Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	float lengthSquared() const;

	/// <summary>������Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	float length() const;

	/// <summary>���K������</summary>
	Vector2& normalize();

	/// <summary>�C�ӎ��ŉ�]����</summary>
	/// <param name="origin">���S�_</param>
	/// <param name="angle">��]��</param>
	Vector2& rotate(const Vector2& origin, float angle);

	/// <summary>�x�N�g���Ɏˉe����</summary>
	/// <param name="v">�Ώۂ̃x�N�g��</param>
	Vector2& projection(const Vector2& v);

	/// <summary>�x�N�g���̂Ȃ��p��Ԃ�</summary>
	float angle(const Vector2& v) const;

public:

	/// <summary>������ɕϊ����ĕԂ�</summary>
	/// <param name="v">�x�N�g��</param>
	static String ToString(const Vector2& v);

	/// <summary>���ς�Ԃ�</summary>
	/// <param name="v1">�x�N�g��</param>
	/// <param name="v2">�x�N�g��</param>
	static float Dot(const Vector2& v1, const Vector2& v2);

	/// <summary>�O�ς�Ԃ�</summary>
	static float Cross(const Vector2& v1, const Vector2& v2);

	/// <summary>�����̓���Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	static float LengthSquared(const Vector2& v);

	/// <summary>������Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	static float Length(const Vector2& v);

	/// <summary>���K�������x�N�g����Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	static Vector2 Nornalize(const Vector2& v);

	/// <summary>�C�ӎ��ŉ�]�����x�N�g���Ԃ�</summary>
	/// <param name="point">�C�ӓ_</param>
	/// <param name="origin">���S�_</param>
	/// <param name="angle">��]��</param>
	static Vector2 Rotate(const Vector2& point, const Vector2& origin, float angle);

	/// <summary>���e�����x�N�g����Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	/// <param name="target">�Ώۂ̃x�N�g��</param>
	static Vector2 Projection(const Vector2& v, const Vector2& target);

	/// <summary>���`��Ԃ����x�N�g����Ԃ�</summary>
	/// <param name="start">�J�n�x�N�g��</param>
	/// <param name="end">�I���x�N�g��</param>
	/// <param name="t">�J�ڗ�</param>
	static Vector2 Lerp(const Vector2& start, const Vector2& end, float t);

	/// <summary>�x�N�g���̂Ȃ��p��Ԃ�</summary>
	static float Angle(const Vector2& v1, const Vector2& v2);

public:

	union
	{
		float elm[2];

		float mat[1][2];

		struct
		{
			float u, v;
		};

		struct
		{
			float x, y;
		};
	};
};

bool operator == (const Vector2& v1, const Vector2& v2);

bool operator != (const Vector2& v1, const Vector2& v2);

Vector2 operator + (const Vector2& v);

Vector2 operator - (const Vector2& v);

Vector2& operator += (Vector2& v1, const Vector2& v2);

Vector2& operator -= (Vector2& v1, const Vector2& v2);

Vector2& operator *= (Vector2& v1, const Vector2& v2);

Vector2& operator *= (Vector2& v, float s);

Vector2& operator /= (Vector2& v1, const Vector2& v2);

Vector2& operator /= (Vector2& v, float s);

Vector2 operator + (const Vector2& v1, const Vector2& v2);

Vector2 operator - (const Vector2& v1, const Vector2& v2);

Vector2 operator * (const Vector2& v1, const Vector2& v2);

Vector2 operator * (const Vector2& v, float s);

Vector2 operator * (float s, const Vector2& v);

Vector2 operator / (const Vector2& v1, const Vector2& v2);

Vector2 operator / (const Vector2& v, float s);
