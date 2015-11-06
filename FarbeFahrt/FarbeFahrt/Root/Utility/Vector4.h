# pragma once

// -------------------------------------------------------------------
// �O�u�錾
// -------------------------------------------------------------------
class Vector3;
class Point4;
class String;

/// <summary>�l�����x�N�g��</summary>
class Vector4
{
public:

	/// <summary>(0, 0, 0)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector4& Zero();

	/// <summary>(1, 1, 1)�ŏ��������ꂽ�x�N�g����Ԃ�</summary>
	static const Vector4& One();

public:

	/// <summary>�R���X�g���N�^</summary>
	Vector4();

	/// <summary>�R�s�[�R���X�g���N�^</summary>
	Vector4(const Vector4& v);

	/// <summary>�v�f���w�肵�č\�z����</summary>
	Vector4(float x, float y, float z, float w);

	/// <summary>�O�����x�N�g����w�v�f���w�肵�č\�z����</summary>
	Vector4(const Vector3& v, float w);

	/// <summary>�l�����_����\�z����</summary>
	explicit Vector4(const Point4& v);

	/// <summary>������Z�q</summary>
	Vector4& operator = (const Vector4& v);

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
	float dot(const Vector4& v) const;

	/// <summary>���K������</summary>
	Vector4& normalize();

	/// <summary>�����̓���Ԃ�</summary>
	float lengthSquared() const;

	/// <summary>������Ԃ�</summary>
	float length() const;

	/// <summary>�ˉe����</summary>
	/// <param name="v">�Ώۂ̃x�N�g��</param>
	Vector4& projection(const Vector4& v);

public:

	/// <summary>������ɕϊ����ĕԂ�</summary>
	/// <param name="v">�x�N�g��</param>
	static String ToString(const Vector4& v);

	/// <summary>���ς�Ԃ�</summary>
	static float Dot(const Vector4& v1, const Vector4& v2);

	/// <summary>�����̓���Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	static float LengthSquared(const Vector4& v);

	/// <summary>������Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	static float Length(const Vector4& v);

	/// <summary>���K�������x�N�g���Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	static Vector4 Normalize(const Vector4& v);

	/// <summary>�ˉe�����x�N�g����Ԃ�</summary>
	/// <param name="v">�x�N�g��</param>
	/// <param name="target">�Ώۂ̃x�N�g��</param>
	static Vector4 Projection(const Vector4& v, const Vector4& target);

	/// <summary>���`��Ԃ����x�N�g����Ԃ�</summary>
	/// <param name="start">�J�n�x�N�g��</param>
	/// <param name="end">�I���x�N�g��</param>
	/// <param name="t">�J�ڗ�</param>
	static Vector4 Lerp(const Vector4& start, const Vector4& end, float t);

public:

	union
	{
		float elm[4];

		float mat[1][4];

		struct
		{
			float r, g, b, a;
		};

		struct
		{
			float x, y, z, w;
		};
	};
};

bool operator == (const Vector4& v1, const Vector4& v2);

bool operator != (const Vector4& v1, const Vector4& v2);

Vector4 operator + (const Vector4& v);

Vector4 operator - (const Vector4& v);

Vector4& operator += (Vector4& v1, const Vector4& v2);

Vector4& operator -= (Vector4& v1, const Vector4& v2);

Vector4& operator *= (Vector4& v1, const Vector4& v2);

Vector4& operator *= (Vector4& v, float s);

Vector4& operator /= (Vector4& v1, const Vector4& v2);

Vector4& operator /= (Vector4& v, float s);

Vector4 operator + (const Vector4& v1, const Vector4& v2);

Vector4 operator - (const Vector4& v1, const Vector4& v2);

Vector4 operator * (const Vector4& v1, const Vector4& v2);

Vector4 operator * (const Vector4& v, float s);

Vector4 operator * (float s, const Vector4& v);

Vector4 operator / (const Vector4& v1, const Vector4& v2);

Vector4 operator / (const Vector4& v, float s);
