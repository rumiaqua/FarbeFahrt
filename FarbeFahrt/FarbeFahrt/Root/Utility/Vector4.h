# pragma once

// -------------------------------------------------------------------
// 前置宣言
// -------------------------------------------------------------------
class Vector3;
class Point4;
class String;

/// <summary>四次元ベクトル</summary>
class Vector4
{
public:

	/// <summary>(0, 0, 0)で初期化されたベクトルを返す</summary>
	static const Vector4& Zero();

	/// <summary>(1, 1, 1)で初期化されたベクトルを返す</summary>
	static const Vector4& One();

public:

	/// <summary>コンストラクタ</summary>
	Vector4();

	/// <summary>コピーコンストラクタ</summary>
	Vector4(const Vector4& v);

	/// <summary>要素を指定して構築する</summary>
	Vector4(float x, float y, float z, float w);

	/// <summary>三次元ベクトルとw要素を指定して構築する</summary>
	Vector4(const Vector3& v, float w);

	/// <summary>四次元点から構築する</summary>
	explicit Vector4(const Point4& v);

	/// <summary>代入演算子</summary>
	Vector4& operator = (const Vector4& v);

public:

	/// <summary>配列に変換する</summary>
	operator float* ();

	/// <summary>配列に変換する</summary>
	operator const float* () const;

public:

	/// <summary>文字列に変換して返す</summary>
	String toString() const;

	/// <summary>内積を返す</summary>
	/// <param name="v">ベクトル</param>
	float dot(const Vector4& v) const;

	/// <summary>正規化する</summary>
	Vector4& normalize();

	/// <summary>長さの二乗を返す</summary>
	float lengthSquared() const;

	/// <summary>長さを返す</summary>
	float length() const;

	/// <summary>射影する</summary>
	/// <param name="v">対象のベクトル</param>
	Vector4& projection(const Vector4& v);

public:

	/// <summary>文字列に変換して返す</summary>
	/// <param name="v">ベクトル</param>
	static String ToString(const Vector4& v);

	/// <summary>内積を返す</summary>
	static float Dot(const Vector4& v1, const Vector4& v2);

	/// <summary>長さの二乗を返す</summary>
	/// <param name="v">ベクトル</param>
	static float LengthSquared(const Vector4& v);

	/// <summary>長さを返す</summary>
	/// <param name="v">ベクトル</param>
	static float Length(const Vector4& v);

	/// <summary>正規化したベクトル返す</summary>
	/// <param name="v">ベクトル</param>
	static Vector4 Normalize(const Vector4& v);

	/// <summary>射影したベクトルを返す</summary>
	/// <param name="v">ベクトル</param>
	/// <param name="target">対象のベクトル</param>
	static Vector4 Projection(const Vector4& v, const Vector4& target);

	/// <summary>線形補間したベクトルを返す</summary>
	/// <param name="start">開始ベクトル</param>
	/// <param name="end">終了ベクトル</param>
	/// <param name="t">遷移率</param>
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
