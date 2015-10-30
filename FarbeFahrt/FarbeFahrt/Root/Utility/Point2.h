# pragma once

# include <DxLib.h>

// -------------------------------------------------------------------
// �O�u�錾
// -------------------------------------------------------------------
class Point3;
class Vector2;
class String;

/// <summary>�񎟌��_</summary>
class Point2
{
public:

	/// <summary>(0, 0)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point2& Zero();

	/// <summary>(1, 1)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point2& One();

	/// <summary>(-1, 0)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point2& Left();

	/// <summary>(1, 0)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point2& Right();

	/// <summary>(0, -1)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point2& Up();

	/// <summary>(0, 1)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point2& Down();

public:

	/// <summary>�R���X�g���N�^</summary>
	Point2();

	/// <summary>�R�s�[�R���X�g���N�^</summary>
	Point2(const Point2& v);

	/// <summary>�v�f���w�肵�č\�z����</summary>
	Point2(int x, int y);

	/// <summary>�O�����_����\�z����</summary>
	explicit Point2(const Point3& v);

	/// <summary>�񎟌��_����\�z����</summary>
	explicit Point2(const Vector2& v);

	/// <summary>DxLib::POINT����\�z����</summary>
	Point2(const POINT& p);

	/// <summary>������Z�q</summary>
	Point2& operator = (const Point2& v);

public:

	/// <summary>�z��ɕϊ�����</summary>
	operator int* ();

	/// <summary>�z��ɕϊ�����</summary>
	operator const int* () const;

	/// <summary>DxLib::POINT�ɕϊ�����</summary>
	operator POINT& ();

	/// <summary>DxLib::POINT�ɕϊ�����</summary>
	operator const POINT& () const;

public:

	/// <summary>������ɕϊ����ĕԂ�</summary>
	String toString() const;

	/// <summary>���ς�Ԃ�</summary>
	/// <param name="v">�_</param>
	int dot(const Point2& v) const;

	/// <summary>�O�ς�Ԃ�</summary>
	/// <param name="v">�_</param>
	int cross(const Point2& v) const;

	/// <summary>�����̓���Ԃ�</summary>
	/// <param name="v">�_</param>
	int lengthSquared() const;

	/// <summary>������Ԃ�</summary>
	/// <param name="v">�_</param>
	float length() const;

public:

	/// <summary>������ɕϊ����ĕԂ�</summary>
	/// <param name="v">�_</param>
	static String ToString(const Point2& v);

	/// <summary>���ς�Ԃ�</summary>
	/// <param name="v1">�_</param>
	/// <param name="v2">�_</param>
	static int Dot(const Point2& v1, const Point2& v2);

	/// <summary>�O�ς�Ԃ�</summary>
	static int Cross(const Point2& v1, const Point2& v2);

	/// <summary>�����̓���Ԃ�</summary>
	/// <param name="v">�_</param>
	static int LengthSquared(const Point2& v);

	/// <summary>������Ԃ�</summary>
	/// <param name="v">�_</param>
	static float Length(const Point2& v);

public:

	union
	{
		int elm[2];

		int mat[1][2];

		struct
		{
			int u, v;
		};

		struct
		{
			int x, y;
		};
	};
};

bool operator == (const Point2& v1, const Point2& v2);

bool operator != (const Point2& v1, const Point2& v2);

Point2 operator + (const Point2& v);

Point2 operator - (const Point2& v);

Point2& operator += (Point2& v1, const Point2& v2);

Point2& operator -= (Point2& v1, const Point2& v2);

Point2& operator *= (Point2& v1, const Point2& v2);

Point2& operator *= (Point2& v, int s);

Point2& operator /= (Point2& v1, const Point2& v2);

Point2& operator /= (Point2& v, int s);

Point2 operator + (const Point2& v1, const Point2& v2);

Point2 operator - (const Point2& v1, const Point2& v2);

Point2 operator * (const Point2& v1, const Point2& v2);

Point2 operator * (const Point2& v, int s);

Point2 operator * (int s, const Point2& v);

Point2 operator / (const Point2& v1, const Point2& v2);

Point2 operator / (const Point2& v, int s);
