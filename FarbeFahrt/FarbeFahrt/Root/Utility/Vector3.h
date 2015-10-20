# pragma once
#include "Dxlib.h"

// -------------------------------------------------------------------
// 前置宣言
// -------------------------------------------------------------------
class Vector4;
class Point3;
class String;

/// <summary>三次元ベクトル</summary>
class Vector3
{
public:

	/// <summary>(0, 0, 0)で初期化されたベクトルを返す</summary>
	static const Vector3& zero();

	/// <summary>(1, 1, 1)で初期化されたベクトルを返す</summary>
	static const Vector3& one();

	/// <summary>(-1, 0, 0)で初期化されたベクトルを返す</summary>
	static const Vector3& left();

	/// <summary>(1, 0, 0)で初期化されたベクトルを返す</summary>
	static const Vector3& right();

	/// <summary>(0, 1, 0)で初期化されたベクトルを返す</summary>
	static const Vector3& up();

	/// <summary>(0, -1, 0)で初期化されたベクトルを返す</summary>
	static const Vector3& down();

	/// <summary>(0, 0, 1)で初期化されたベクトルを返す</summary>
	static const Vector3& forward();

	/// <summary>(0, 0, -1)で初期化されたベクトルを返す</summary>
	static const Vector3& backward();

public:

	/// <summary>コンストラクタ</summary>
	Vector3();

	/// <summary>コピーコンストラクタ</summary>
	Vector3(const Vector3& v);

	/// <summary>要素を指定して構築する</summary>
	Vector3(float x, float y, float z);

	/// <summary>四次元ベクトルから構築する</summary>
	explicit Vector3(const Vector4& v);

	/// <summary>三次元点から構築する</summary>
	explicit Vector3(const Point3& v);

	/// <summary>DxLibのベクトルから構築する</summary>
	explicit Vector3(const VECTOR& v);

	/// <summary>代入演算子</summary>
	Vector3& operator = (const Vector3& v);

public:

	/// <summary>配列に変換する</summary>
	operator float* ();

	/// <summary>配列に変換する</summary>
	operator const float* () const;

	operator DxLib::VECTOR& ();

	operator const DxLib::VECTOR&() const;

public:

	/// <summary>文字列に変換して返す</summary>
	String toString() const;

	/// <summary>内積を返す</summary>
	/// <param name="v">ベクトル</param>
	float dot(const Vector3& v) const;

	/// <summary>外積を返す</summary>
	/// <param name="v">ベクトル</param>
	Vector3 cross(const Vector3& v) const;

	/// <summary>長さの二乗を返す</summary>
	/// <param name="v">ベクトル</param>
	float lengthSquared() const;

	/// <summary>長さを返す</summary>
	/// <param name="v">ベクトル</param>
	float length() const;

	/// <summary>正規化する</summary>
	Vector3& normalize();

	/// <summary>任意軸で回転する</summary>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	Vector3& rotate(const Vector3& axis, float angle);

	/// <summary>ベクトルに射影する</summary>
	/// <param name="v">対象のベクトル</param>
	Vector3& projection(const Vector3& v);

	/// <summary>ベクトルのなす角を返す</summary>
	float angle(const Vector3& v) const;

public:

	/// <summary>文字列に変換して返す</summary>
	/// <param name="v">ベクトル</param>
	static String toString(const Vector3& v);

	/// <summary>内積を返す</summary>
	/// <param name="v1">ベクトル</param>
	/// <param name="v2">ベクトル</param>
	static float dot(const Vector3& v1, const Vector3& v2);

	/// <summary>外積を返す</summary>
	static Vector3 cross(const Vector3& v1, const Vector3& v2);

	/// <summary>長さの二乗を返す</summary>
	/// <param name="v">ベクトル</param>
	static float lengthSquared(const Vector3& v);

	/// <summary>長さを返す</summary>
	/// <param name="v">ベクトル</param>
	static float length(const Vector3& v);

	/// <summary>正規化したベクトルを返す</summary>
	/// <param name="v">ベクトル</param>
	static Vector3 normalize(const Vector3& v);

	/// <summary>任意軸で回転したベクトル返す</summary>
	/// <param name="point">任意点</param>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	static Vector3 rotate(const Vector3& point, const Vector3& axis, float angle);

	/// <summary>投影したベクトルを返す</summary>
	/// <param name="v">ベクトル</param>
	/// <param name="target">対象のベクトル</param>
	static Vector3 projection(const Vector3& v, const Vector3& target);

	/// <summary>線形補間したベクトルを返す</summary>
	/// <param name="start">開始ベクトル</param>
	/// <param name="end">終了ベクトル</param>
	/// <param name="t">遷移率</param>
	static Vector3 lerp(const Vector3& start, const Vector3& end, float t);

	/// <summary>ベクトルのなす角を返す</summary>
	static float angle(const Vector3& v1, const Vector3& v2);

	/// <summary>球面線形補間したベクトルを返す</summary>
	/// <param name="start">開始ベクトル</param>
	/// <param name="end">終了ベクトル</param>
	/// <param name="t">遷移率</param>
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
