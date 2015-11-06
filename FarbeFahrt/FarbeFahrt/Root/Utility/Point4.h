# pragma once

// -------------------------------------------------------------------
// �O�u�錾
// -------------------------------------------------------------------
class Point3;
class Vector4;
class String;

/// <summary>�l�����_</summary>
class Point4
{
public:

	/// <summary>(0, 0, 0, 0)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point4& zero();

	/// <summary>(1, 1, 1, 1)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point4& one();

public:

	/// <summary>�R���X�g���N�^</summary>
	Point4();

	/// <summary>�R�s�[�R���X�g���N�^</summary>
	Point4(const Point4& v);

	/// <summary>�v�f���w�肵�č\�z����</summary>
	Point4(int x, int y, int z, int w);

	/// <summary>�O�����_��w�v�f���w�肵�č\�z����</summary>
	Point4(const Point3& v, int w);

	/// <summary>�l�����x�N�g������\�z����</summary>
	explicit Point4(const Vector4& v);

	/// <summary>������Z�q</summary>
	Point4& operator = (const Point4& v);

public:

	/// <summary>�z��ɕϊ�����</summary>
	operator int* ();

	/// <summary>�z��ɕϊ�����</summary>
	operator const int* () const;

public:

	/// <summary>������ɕϊ����ĕԂ�</summary>
	String toString() const;

	/// <summary>���ς�Ԃ�</summary>
	/// <param name="v">�_</param>
	int dot(const Point4& v) const;

	/// <summary>�����̓���Ԃ�</summary>
	int lengthSquared() const;

	/// <summary>������Ԃ�</summary>
	float length() const;

public:

	/// <summary>������ɕϊ����ĕԂ�</summary>
	/// <param name="v">�_</param>
	static String ToString(const Point4& v);

	/// <summary>���ς�Ԃ�</summary>
	static int Dot(const Point4& v1, const Point4& v2);

	/// <summary>�����̓���Ԃ�</summary>
	/// <param name="v">�_</param>
	static int LengthSquared(const Point4& v);

	/// <summary>������Ԃ�</summary>
	/// <param name="v">�_</param>
	static float Length(const Point4& v);

public:

	union
	{
		int elm[4];

		int mat[1][4];

		struct
		{
			int r, g, b, a;
		};

		struct
		{
			int x, y, z, w;
		};
	};
};

bool operator == (const Point4& v1, const Point4& v2);

bool operator != (const Point4& v1, const Point4& v2);

Point4 operator + (const Point4& v);

Point4 operator - (const Point4& v);

Point4& operator += (Point4& v1, const Point4& v2);

Point4& operator -= (Point4& v1, const Point4& v2);

Point4& operator *= (Point4& v1, const Point4& v2);

Point4& operator *= (Point4& v, int s);

Point4& operator /= (Point4& v1, const Point4& v2);

Point4& operator /= (Point4& v, int s);

Point4 operator + (const Point4& v1, const Point4& v2);

Point4 operator - (const Point4& v1, const Point4& v2);

Point4 operator * (const Point4& v1, const Point4& v2);

Point4 operator * (const Point4& v, int s);

Point4 operator * (int s, const Point4& v);

Point4 operator / (const Point4& v1, const Point4& v2);

Point4 operator / (const Point4& v, int s);
