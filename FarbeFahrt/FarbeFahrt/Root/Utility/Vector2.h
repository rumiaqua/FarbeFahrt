# pragma once

// -------------------------------------------------------------------
// 前置宣言
// -------------------------------------------------------------------
class Vector3;
class Point2;
class String;

/// <summary>二次元ベクトル</summary>
class Vector2
{
public:

	/// <summary>(0, 0)で初期化されたベクトルを返す</summary>
	static const Vector2& zero();

	/// <summary>(1, 1)で初期化されたベクトルを返す</summary>
	static const Vector2& one();

	/// <summary>(-1, 0)で初期化されたベクトルを返す</summary>
	static const Vector2& left();

	/// <summary>(1, 0)で初期化されたベクトルを返す</summary>
	static const Vector2& right();

	/// <summary>(0, -1)で初期化されたベクトルを返す</summary>
	static const Vector2& up();

	/// <summary>(0, 1)で初期化されたベクトルを返す</summary>
	static const Vector2& down();

public:

	/// <summary>コンストラクタ</summary>
	Vector2();

	/// <summary>コピーコンストラクタ</summary>
	Vector2(const Vector2& v);

	/// <summary>要素を指定して構築する</summary>
	Vector2(float x, float y);

	/// <summary>三次元ベクトルから構築する</summary>
	Vector2(const Vector3& v);

	/// <summary>二次元点から構築する</summary>
	Vector2(const Point2& v);

	/// <summary>代入演算子</summary>
	Vector2& operator = (const Vector2& v);

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
	float dot(const Vector2& v) const;

	/// <summary>外積を返す</summary>
	/// <param name="v">ベクトル</param>
	float cross(const Vector2& v) const;

	/// <summary>長さの二乗を返す</summary>
	/// <param name="v">ベクトル</param>
	float lengthSquared() const;

	/// <summary>長さを返す</summary>
	/// <param name="v">ベクトル</param>
	float length() const;

	/// <summary>正規化する</summary>
	Vector2& normalize();

	/// <summary>任意軸で回転する</summary>
	/// <param name="origin">中心点</param>
	/// <param name="angle">回転量</param>
	Vector2& rotate(const Vector2& origin, float angle);

	/// <summary>ベクトルに射影する</summary>
	/// <param name="v">対象のベクトル</param>
	Vector2& projection(const Vector2& v);

	/// <summary>ベクトルのなす角を返す</summary>
	float angle(const Vector2& v) const;

public:

	/// <summary>文字列に変換して返す</summary>
	/// <param name="v">ベクトル</param>
	static String toString(const Vector2& v);

	/// <summary>内積を返す</summary>
	/// <param name="v1">ベクトル</param>
	/// <param name="v2">ベクトル</param>
	static float dot(const Vector2& v1, const Vector2& v2);

	/// <summary>外積を返す</summary>
	static float cross(const Vector2& v1, const Vector2& v2);

	/// <summary>長さの二乗を返す</summary>
	/// <param name="v">ベクトル</param>
	static float lengthSquared(const Vector2& v);

	/// <summary>長さを返す</summary>
	/// <param name="v">ベクトル</param>
	static float length(const Vector2& v);

	/// <summary>正規化したベクトルを返す</summary>
	/// <param name="v">ベクトル</param>
	static Vector2 normalize(const Vector2& v);

	/// <summary>任意軸で回転したベクトル返す</summary>
	/// <param name="point">任意点</param>
	/// <param name="origin">中心点</param>
	/// <param name="angle">回転量</param>
	static Vector2 rotate(const Vector2& point, const Vector2& origin, float angle);

	/// <summary>投影したベクトルを返す</summary>
	/// <param name="v">ベクトル</param>
	/// <param name="target">対象のベクトル</param>
	static Vector2 projection(const Vector2& v, const Vector2& target);

	/// <summary>線形補間したベクトルを返す</summary>
	/// <param name="start">開始ベクトル</param>
	/// <param name="end">終了ベクトル</param>
	/// <param name="t">遷移率</param>
	static Vector2 lerp(const Vector2& start, const Vector2& end, float t);

	/// <summary>ベクトルのなす角を返す</summary>
	static float angle(const Vector2& v1, const Vector2& v2);

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
