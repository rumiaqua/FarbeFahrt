# pragma once

# include <DxLib.h>

// -------------------------------------------------------------------
// 前置宣言
// -------------------------------------------------------------------
class Point3;
class Vector2;
class String;

/// <summary>二次元点</summary>
class Point2
{
public:

	/// <summary>(0, 0)で初期化された点を返す</summary>
	static const Point2& Zero();

	/// <summary>(1, 1)で初期化された点を返す</summary>
	static const Point2& One();

	/// <summary>(-1, 0)で初期化された点を返す</summary>
	static const Point2& Left();

	/// <summary>(1, 0)で初期化された点を返す</summary>
	static const Point2& Right();

	/// <summary>(0, -1)で初期化された点を返す</summary>
	static const Point2& Up();

	/// <summary>(0, 1)で初期化された点を返す</summary>
	static const Point2& Down();

public:

	/// <summary>コンストラクタ</summary>
	Point2();

	/// <summary>コピーコンストラクタ</summary>
	Point2(const Point2& v);

	/// <summary>要素を指定して構築する</summary>
	Point2(int x, int y);

	/// <summary>三次元点から構築する</summary>
	explicit Point2(const Point3& v);

	/// <summary>二次元点から構築する</summary>
	explicit Point2(const Vector2& v);

	/// <summary>DxLib::POINTから構築する</summary>
	Point2(const POINT& p);

	/// <summary>代入演算子</summary>
	Point2& operator = (const Point2& v);

public:

	/// <summary>配列に変換する</summary>
	operator int* ();

	/// <summary>配列に変換する</summary>
	operator const int* () const;

	/// <summary>DxLib::POINTに変換する</summary>
	operator POINT& ();

	/// <summary>DxLib::POINTに変換する</summary>
	operator const POINT& () const;

public:

	/// <summary>文字列に変換して返す</summary>
	String toString() const;

	/// <summary>内積を返す</summary>
	/// <param name="v">点</param>
	int dot(const Point2& v) const;

	/// <summary>外積を返す</summary>
	/// <param name="v">点</param>
	int cross(const Point2& v) const;

	/// <summary>長さの二乗を返す</summary>
	/// <param name="v">点</param>
	int lengthSquared() const;

	/// <summary>長さを返す</summary>
	/// <param name="v">点</param>
	float length() const;

public:

	/// <summary>文字列に変換して返す</summary>
	/// <param name="v">点</param>
	static String ToString(const Point2& v);

	/// <summary>内積を返す</summary>
	/// <param name="v1">点</param>
	/// <param name="v2">点</param>
	static int Dot(const Point2& v1, const Point2& v2);

	/// <summary>外積を返す</summary>
	static int Cross(const Point2& v1, const Point2& v2);

	/// <summary>長さの二乗を返す</summary>
	/// <param name="v">点</param>
	static int LengthSquared(const Point2& v);

	/// <summary>長さを返す</summary>
	/// <param name="v">点</param>
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
