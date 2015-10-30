# pragma once

// -------------------------------------------------------------------
// 前置宣言
// -------------------------------------------------------------------
class Point3;
class Vector4;
class String;

/// <summary>四次元点</summary>
class Point4
{
public:

	/// <summary>(0, 0, 0, 0)で初期化された点を返す</summary>
	static const Point4& zero();

	/// <summary>(1, 1, 1, 1)で初期化された点を返す</summary>
	static const Point4& one();

public:

	/// <summary>コンストラクタ</summary>
	Point4();

	/// <summary>コピーコンストラクタ</summary>
	Point4(const Point4& v);

	/// <summary>要素を指定して構築する</summary>
	Point4(int x, int y, int z, int w);

	/// <summary>三次元点とw要素を指定して構築する</summary>
	Point4(const Point3& v, int w);

	/// <summary>四次元ベクトルから構築する</summary>
	explicit Point4(const Vector4& v);

	/// <summary>代入演算子</summary>
	Point4& operator = (const Point4& v);

public:

	/// <summary>配列に変換する</summary>
	operator int* ();

	/// <summary>配列に変換する</summary>
	operator const int* () const;

public:

	/// <summary>文字列に変換して返す</summary>
	String toString() const;

	/// <summary>内積を返す</summary>
	/// <param name="v">点</param>
	int dot(const Point4& v) const;

	/// <summary>長さの二乗を返す</summary>
	int lengthSquared() const;

	/// <summary>長さを返す</summary>
	float length() const;

public:

	/// <summary>文字列に変換して返す</summary>
	/// <param name="v">点</param>
	static String ToString(const Point4& v);

	/// <summary>内積を返す</summary>
	static int Dot(const Point4& v1, const Point4& v2);

	/// <summary>長さの二乗を返す</summary>
	/// <param name="v">点</param>
	static int LengthSquared(const Point4& v);

	/// <summary>長さを返す</summary>
	/// <param name="v">点</param>
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
