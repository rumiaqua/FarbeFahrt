# pragma once

# include <string>

// -------------------------------------------------------------------
// �O�u�錾
// -------------------------------------------------------------------
class Point4;
class Vector3;


/// <summary>�O�����_</summary>
class Point3
{
public:

	/// <summary>(0, 0, 0)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point3& Zero();

	/// <summary>(1, 1, 1)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point3& One();

	/// <summary>(-1, 0, 0)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point3& Left();

	/// <summary>(1, 0, 0)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point3& Right();

	/// <summary>(0, 1, 0)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point3& Up();

	/// <summary>(0, -1, 0)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point3& Down();

	/// <summary>(0, 0, 1)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point3& Forward();

	/// <summary>(0, 0, -1)�ŏ��������ꂽ�_��Ԃ�</summary>
	static const Point3& Backward();

public:

	/// <summary>�R���X�g���N�^</summary>
	Point3();

	/// <summary>�R�s�[�R���X�g���N�^</summary>
	Point3(const Point3& v);

	/// <summary>�v�f���w�肵�č\�z����</summary>
	Point3(int x, int y, int z);

	/// <summary>�l�����_����\�z����</summary>
	explicit Point3(const Point4& v);

	/// <summary>�O�����x�N�g������\�z����</summary>
	explicit Point3(const Vector3& v);

	/// <summary>������Z�q</summary>
	Point3& operator = (const Point3& v);

public:

	/// <summary>�z��ɕϊ�����</summary>
	operator int* ();

	/// <summary>�z��ɕϊ�����</summary>
	operator const int* () const;

public:

	/// <summary>������ɕϊ����ĕԂ�</summary>
	std::string toString() const;

	/// <summary>���ς�Ԃ�</summary>
	/// <param name="v">�_</param>
	int dot(const Point3& v) const;

	/// <summary>�O�ς�Ԃ�</summary>
	/// <param name="v">�_</param>
	Point3 cross(const Point3& v) const;

	/// <summary>�����̓���Ԃ�</summary>
	/// <param name="v">�_</param>
	int lengthSquared() const;

	/// <summary>������Ԃ�</summary>
	/// <param name="v">�_</param>
	float length() const;

public:

	/// <summary>������ɕϊ����ĕԂ�</summary>
	/// <param name="v">�_</param>
	static std::string ToString(const Point3& v);

	/// <summary>���ς�Ԃ�</summary>
	/// <param name="v1">�_</param>
	/// <param name="v2">�_</param>
	static int Dot(const Point3& v1, const Point3& v2);

	/// <summary>�O�ς�Ԃ�</summary>
	static Point3 Cross(const Point3& v1, const Point3& v2);

	/// <summary>�����̓���Ԃ�</summary>
	/// <param name="v">�_</param>
	static int LengthSquared(const Point3& v);

	/// <summary>������Ԃ�</summary>
	/// <param name="v">�_</param>
	static float Length(const Point3& v);

public:

	union
	{
		int elm[3];

		int mat[1][3];

		struct
		{
			int r, g, b;
		};

		struct
		{
			int x, y, z;
		};
	};
};

bool operator == (const Point3& v1, const Point3& v2);

bool operator != (const Point3& v1, const Point3& v2);

Point3 operator + (const Point3& v);

Point3 operator - (const Point3& v);

Point3& operator += (Point3& v1, const Point3& v2);

Point3& operator -= (Point3& v1, const Point3& v2);

Point3& operator *= (Point3& v1, const Point3& v2);

Point3& operator *= (Point3& v, int s);

Point3& operator /= (Point3& v1, const Point3& v2);

Point3& operator /= (Point3& v, int s);

Point3 operator + (const Point3& v1, const Point3& v2);

Point3 operator - (const Point3& v1, const Point3& v2);

Point3 operator * (const Point3& v1, const Point3& v2);

Point3 operator * (const Point3& v, int s);

Point3 operator * (int s, const Point3& v);

Point3 operator / (const Point3& v1, const Point3& v2);

Point3 operator / (const Point3& v, int s);
